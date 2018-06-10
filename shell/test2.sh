o hello; echo there
filename=ttt.sh
if [ -e "$filename" ]; then    # 注意: "if"和"then"需要分隔，-e是判断文件存在否
    echo "File $filename exists."; cp $filename $filename.bak
else
    echo "File $filename not found."; touch $filename
fi; echo "File test complete."
