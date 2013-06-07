/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#pragma once

/**
 * *���イ���I*
 * ���̃N���X�ꗗ�ɂ́A���ۓI�ȃN���X���̂݁��L�q����B
 * ���ۂ̕`�惉�C�u������A�z�u���W�b�N�Ɉˑ������N���X�́APluginOrganizer�Ȃǂ�p����
 * �ˑ����������邱�ƁB
 */
namespace saccubus{
class Saccubus;
class Adapter;
class PluginOrganizer;

namespace draw{
class Sprite;
class RawSprite;
class Renderer;
class Context;
class CommentFactory;
class ShapeFactory;
}

namespace logging{
class Exception;
}

namespace layer{
namespace item{
class Comment;
class Button;
class Label;
class Shape;
}
class Layer;
class CommentLayer;
class ThreadLayer;
class VideoLayer;
class NekomataSystem;
}

namespace python{
class PyBridge;
}

namespace util{
class Bundle;
}

}
