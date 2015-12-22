#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   TreeWriter.py
#        \author   chenghuige  
#          \date   2014-10-02 20:32:25.744069
#   \Description  
# ==============================================================================

import sys
from BinaryTree import *
import pygraphviz as pgv
'''
treeWriter with func wite can write a binary tree to tree.png or user spcified
file
'''
class TreeWriter():
		def __init__(self, tree = None):
				self.num = 1       #mark each visible node as its key
				self.num2 = -1     #makk each invisible node as its key
				self.tree = tree 
				self.use_invisable_node = False 
				
		def Write(self, outfile = 'tree.png'):
				def writeHelp(root, A):
						if not root:
								return
						
						p = str(self.num)
						self.num += 1
						A.add_node(p, **root.attr)
						q = None
						r = None
						
						if root.left:
								q = writeHelp(root.left, A)
								A.add_edge(p, q, **root.leftEdgeAttr)
						if root.right:
								r = writeHelp(root.right, A)
								A.add_edge(p, r, **root.rightEdgeAttr)
								
						if not self.use_invisable_node:
							return p

						if q or r:
								if not q:
										q = str(self.num2)
										self.num2 -= 1
										A.add_node(q, style = 'invis')
										A.add_edge(p, q, style = 'invis')
								if not r:
										r = str(self.num2)
										self.num2 -= 1
										A.add_node(r, style = 'invis')
										A.add_edge(p, r, style = 'invis')
								l = str(self.num2)
								self.num2 -= 1
								A.add_node(l, style = 'invis')
								A.add_edge(p, l, style = 'invis')
								B = A.add_subgraph([q, l, r], rank = 'same')
								B.add_edge(q, l, style = 'invis')
								B.add_edge(l, r, style = 'invis')
						
						return p  #return key root node
										
				self.A = pgv.AGraph(directed=True,strict=True)
				writeHelp(self.tree.root, self.A)
				self.A.graph_attr['epsilon']='0.001'
				#self.A.layout(prog='dot')
				#print self.A.string() # print dot file to standard output
				self.A.layout('dot') # layout with dot
				self.A.draw(outfile) # write to file        
				
	
if __name__ == '__main__':
		tree = BinaryTree()
		tree.CreateTree(-1)
		tree.InorderTravel()
		writer = TreeWriter(tree)
		if len(sys.argv) > 1:
				outfile = sys.argv[1]
				writer.Write(outfile) #write result to outfile
		else:
				writer.Write() #write result to tree.png


 
