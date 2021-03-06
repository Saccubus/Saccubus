/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include <iostream>
#include <SDL2/SDL.h>
#include <cinamo/Logger.h>
#include "../../saccubus/Saccubus.h"
#include "../../saccubus/draw/Renderer.h"
#include "../../saccubus/logging/Exception.h"
using namespace std;
namespace entry_points {
namespace cli {
const unsigned int FACTOR = 3;
const unsigned int FACTORED_INTERVAL = 3*1000/30;

class CLIAdapter : public saccubus::Adapter
{
private:
	saccubus::Saccubus & parent;
public:
	CLIAdapter(saccubus::Saccubus & parent)
	:parent(parent)
	,window(0)
	,windowSurface(0)
	{
	}
	virtual ~CLIAdapter()
	{
		if(this->window){
			SDL_FreeSurface(this->windowSurface);
			SDL_DestroyWindow(this->window);
		}
	}
private:
	SDL_Window* window;
	SDL_Surface* windowSurface;
	void initSDL(int width, int height){
		this->window = SDL_CreateWindow("SaccubusCLI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
		if(!this->window) throw saccubus::logging::Exception(__FILE__, __LINE__, "Failed to create window: %s", SDL_GetError());
		this->windowSurface = SDL_GetWindowSurface(this->window);
		if(!this->windowSurface) throw saccubus::logging::Exception(__FILE__, __LINE__, "Failed to get SDL window surface: %s", SDL_GetError());
	}
public:
	/**
	 * 最初や、ニワン語でjumpが起こった時に呼ばれる。
	 * このコールの次のdraw()には、ちゃんと指定された動画の内容を渡すこと。
	 */
	virtual void onVideoChanged(std::string const& videoId, std::string const& filepath)
	{
		initSDL(640, 480);
	}
public:
	void loop(){
		unsigned long long now = 0;//SDL_GetTicks();
		unsigned long long nextFactored = now*FACTOR+FACTORED_INTERVAL;
		unsigned long long fpsTime = now;
		unsigned int fps = 0;
		while(1) {
			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				switch (e.type) {
				case SDL_QUIT:
					return;
				case SDL_MOUSEBUTTONDOWN:
					if(SDL_BUTTON_LEFT == e.button.button){
						parent.click(e.button.x, e.button.y);
					}
					break;
				default:
					break;
				}
			}

			SDL_FillRect(windowSurface, 0, SDL_MapRGBA(windowSurface->format, 255, 255, 255, 255));
			SDL_LockSurface(windowSurface);
			{
				std::shared_ptr<saccubus::draw::Context> ctx =
						parent.createContext(saccubus::draw::Renderer::ARGB32, windowSurface->pixels, windowSurface->w, windowSurface->h, windowSurface->pitch);
				parent.draw(ctx, std::shared_ptr<saccubus::draw::Sprite>(), now/1000.0);
			}
			SDL_UnlockSurface(windowSurface);
			SDL_UpdateWindowSurface(this->window);

			++fps;
			now = SDL_GetTicks();
			if (now - fpsTime >= 1000) {
				printf("FPS:%d\n", fps);
				fpsTime += 1000;
				fps = 0;
			}

			uint32_t nowFactored = now * FACTOR;
			if (nowFactored < nextFactored) {
				SDL_Delay((nextFactored - nowFactored) / FACTOR);
			}
			nextFactored += FACTORED_INTERVAL;
		}
	}
	/**
	 * ニワン語でseekが起こった時に呼ばれる。
	 * このコールの次のdraw()には、ちゃんと指定された動画の内容を渡すこと。
	 */
	virtual void onSeek(std::string const& videoId, float vpos)
	{
	}
};

int main(int argc, char** argv) {
	saccubus::Saccubus sacc(std::cout, argc, argv);
	CLIAdapter adapter(sacc);
	sacc.init(&adapter);

	adapter.loop();

	return 0;
}

}}

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	try {
		int result = entry_points::cli::main(argc, argv);
		SDL_Quit();
		return result;
	} catch (saccubus::logging::Exception& e) {
		std::cerr << "Saccubus Exception caught." << e.what() << std::endl;
		std::cerr.flush();
		SDL_Quit();
		return -1;
	} catch (std::exception& e) {
		std::cerr << "Standard Exception caught." << e.what() << std::endl;
		std::cerr.flush();
		SDL_Quit();
		return -2;
	} catch (...) {
		std::cerr << "Unknwon Exception caught." << std::endl;
		std::cerr.flush();
		SDL_Quit();
		return -3;
	}
}
