#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   BinaryTree.py
#        \author   chenghuige  
#          \date   2014-10-02 20:32:07.662034
#   \Description  
# ==============================================================================

#Notice the differnce of creating tree code with c++, python does not
#support reference the same as c++ not pointer to pointer in python I think

#Author goldenlock_pku
'''
Ilustrate the create binary tree with user input
inorder travel 
'''
class Node():
    '''
    node will be used in BinaryTree
    '''
    def __init__(self,elem, left = None, right = None, colorAttribute = 'black', leftEdgeAttribute = '', rightEdgeAttribute = ''):
        self.elem = elem
        self.left = left
        self.right = right
        self.colorAttribute = colorAttribute
        self.leftEdgeAttribute = leftEdgeAttribute
        self.rightEdgeAttribute = rightEdgeAttribute
    def __str__(self):
        return str(self.elem)

class BinaryTree():
    def __init__(self,root = None):
        self.root = root
    
    def CreateTree(self, endMark = -1):
        '''create a binary tree with user input'''
        def createTreeHelp(endMark = -1):
            elem = raw_input();
            if (elem == str(endMark)):
                return None
            root = Node(elem)
            root.left = createTreeHelp(endMark)
            root.right = createTreeHelp(endMark)
            return root        
        print('Please input the binary tree data wit ' + str(endMark)\
            +' as endmark')        
        elem = raw_input()
        self.root = Node(elem)
        self.root.left = createTreeHelp(endMark)
        self.root.right = createTreeHelp(endMark)
        
    def InorderTravel(self):
        def inorderTravelHelp(root):
            if not root:
                return 
            inorderTravelHelp(root.left)
            print(root)
            inorderTravelHelp(root.right)        
        inorderTravelHelp(self.root)

 
