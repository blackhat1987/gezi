
import sys,os
sys.path.append('./')
import gezi 

for line in sys.stdin:
	try:
		l = line.rstrip('\n').split('\t')
		uid = l[0]
		title = l[1].decode('utf8').encode('gbk', 'ignore')
		content = l[2].decode('utf8').encode('gbk', 'ignore')
		content = gezi.normalize_str(gezi.strip_html(content))
		if gezi.is_thread(title):
			print uid + '\t' + title 
		else:
			print uid + '\t' + gezi.get_real_title(title)
		if len(content) > 0:
			print uid + '\t' + content
	except Exception:
		continue
 
