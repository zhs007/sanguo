# sanguo
这是一个用cocosd-x 3.6写的三国策略游戏。

现在处于游戏内核阶段，所以是一个纯c++的项目。

工具
---
代码里面会包括一组小工具，目前的思路会是尽可能利用用户本来就很熟悉的工具，而我们通过小工具做自动转换，保证生成的最终数据文件是我们可用的。

csvtools
---
游戏里面需要一组配置表，我们用excel表格，配置表的原始资源在res/static里面，默认情况下，一个文件我们只使用第一个表格。

csvtools是使用nodejs写的小工具，跨平台的，mac、windows下都可以使用，貌似也不需要安装excel。

csvtools使用[xlsx2csv](https://github.com/zhs007/xlsx2csv)来处理xlsx到csv的转换。

使用csvtools以前，需要在csvtools目录下，执行

```
npm install
```

由于csvtools使用了一些第三方库，如果第三方库有更新，会需要执行

```
npm update
```

执行csvtools很简单，就是

```
node csvtools.js
```

这样就会把所有的配置表，导成最终程序读取的目标文件。

所以，如果修改了配置表，需要自己执行csvtools同步一下（过程应该还是比较简单的）。