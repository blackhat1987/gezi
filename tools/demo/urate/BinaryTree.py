#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   BinaryTree.py
#        \author   chenghuige  
#          \date   2014-10-02 20:32:07.662034
#   \Description  
# ==============================================================================

class Node():
		def __init__(self):
				self.attr = {}

				self.left = None
				self.right = None

				self.leftEdgeAttr = {}
				self.rightEdgeAttr = {}

		def __str__(self):
				return str(self.attr)

class BinaryTree():
		def __init__(self,root = None):
				self.root = root
				
		def InorderTravel(self):
				def inorderTravelHelp(root):
						if not root:
								return 
						inorderTravelHelp(root.left)
						print(root)
						inorderTravelHelp(root.right)        
				inorderTravelHelp(self.root)

 
