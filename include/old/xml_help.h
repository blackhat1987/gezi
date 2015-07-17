/* 
 * File:   xml_help.h
 * Author: chenghuige
 *
 * Created on 2010��3��4��, ����1:12
 *
 *  ���tinyXML���һЩhelp ��
 *
 */

#ifndef _XML_HELP_H
#define	_XML_HELP_H
#include "tinyxml.h"

#define XML_HeadLink(parent, son) \
           TiXmlElement * son##Element = new TiXmlElement(#son);\
           parent.LinkEndChild(son##Element)

//�ڲ��ڵ� ���ڵ� ���ӵ� �ӽڵ㣬��ҪԤ�ȶ���� TinyXML* sonElement
#define XML_Link(parent, son) \
           TiXmlElement *son##Element = new TiXmlElement(#son);\
           parent##Element->LinkEndChild(son##Element)

#define XML_RenameLink(parent, son, name) \
           TiXmlElement *son##Element = new TiXmlElement(#name);\
           parent##Element->LinkEndChild(son##Element)

//�����ڵ㵽��������text, ��"abc"
#define XML_LinkEnd(node, text)\
            node##Element->LinkEndChild(new TiXmlText(text))

#define XML_LinkEndStr(node, text)\
            node##Element->LinkEndChild(new TiXmlText(text.c_str()))

#endif	/* _XML_HELP_H */

