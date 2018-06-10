#!/bin/bash
#!/bin/bash

if [ ! 't.txt' ];
then
    touch t.txt
fi
echo 'test text' > t.txt
cp t.{txt,back}

