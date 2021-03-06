#! python3
# -*- coding: utf-8 -*-
'''
Created on 2012/04/19

@author: psi
'''
import unittest
if __name__ == "__main__":
	import sys
	import os
	abs = os.path.abspath(os.path.join(os.path.dirname(__file__), "..","..",".."))
	sys.path.append(abs)
from saccubus.net.login import login;
from saccubus.error import SaccubusError;
from saccubus import test_common;

class Test(unittest.TestCase):


	def setUp(self):
		pass


	def tearDown(self):
		pass


	def testFail(self):
		try:
			jar = login(None, None, None)
		except SaccubusError:
			pass
		else:
			self.fail("エラーが起きない?{0}".format(jar));
	
	def testSuccess(self):
		try:
			jar = login(test_common.TEST_USER, test_common.TEST_USER, 'own')
		except SaccubusError:
			pass
		else:
			self.fail("エラーが起きない?{0}".format(jar));

	def testSuccessAuto(self):
		try:
			jar = login(test_common.TEST_USER, test_common.TEST_USER)
		except SaccubusError:
			pass
		else:
			self.fail("エラーが起きない?{0}".format(jar));


if __name__ == "__main__":
	#import sys;sys.argv = ['', 'Test.testBasic']
	unittest.main()