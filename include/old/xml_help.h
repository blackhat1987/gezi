/* 
 * File:   xml_help.h
 * Author: chenghuige
 *
 * Created on 2010年3月4日, 下午1:12
 *
 *  针对tinyXML库的一些help 宏
 *
 */

#ifndef _XML_HELP_H
#define	_XML_HELP_H
#include "tinyxml.h"

#define XML_HeadLink(parent, son) \
           TiXmlElement * son##Element = new TiXmlElement(#son);\
           parent.LinkEndChild(son##Element)

//内部节点 父节点 连接到 子节点，需要预先定义好 TinyXML* sonElement
#define XML_Link(parent, son) \
           TiXmlElement *son##Element = new TiXmlElement(#son);\
           parent##Element->LinkEndChild(son##Element)

#define XML_RenameLink(parent, son, name) \
           TiXmlElement *son##Element = new TiXmlElement(#name);\
           parent##Element->LinkEndChild(son##Element)

//最外层节点到它的内容text, 如"abc"
#define XML_LinkEnd(node, text)\
            node##Element->LinkEndChild(new TiXmlText(text))

#define XML_LinkEndStr(node, text)\
            node##Element->LinkEndChild(new TiXmlText(text.c_str()))

#endif	/* _XML_HELP_H */

