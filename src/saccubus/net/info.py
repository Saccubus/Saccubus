#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/03/29

@author: psi
'''

INFO_API_URL="http://flapi.nicovideo.jp/api/getflv/{0}"

import urllib;
def getInfo(jar, videoid):
	url = INFO_API_URL.format(videoid);
	resp = urllib.request.build_opener(urllib.request.HTTPCookieProcessor(jar)).open(url);
	content = resp.read().decode('ascii')
	urllib.parse._implicit_encoding='utf-8'
	urllib.parse._implicit_errors='strict'
	_info = urllib.parse.parse_qsl(content, encoding='utf-8', errors='replace');
	resp.close();
	return dict(_info);
	