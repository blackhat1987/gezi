cat $1 | python ./add-static-def.py | python ./fix-pyplusplus.py | python ./fix-abstract-class.py | python ./fix-constructor.py | python ./fix-pyplusplus-vec.py | python ./fix-pyplusplus-map.py | python ./fix-add-more-vector.py > $1.ok
mv $1 $1.bak
mv $1.ok $1
