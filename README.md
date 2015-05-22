# sanguo
这是一个用cocosd-x 3.6写的三国策略游戏。

现在处于游戏内核阶段，所以是一个纯c++的项目。

编码集
---
由于项目在windows、mac下配合开发，为了方便跨平台编辑且中文正确识别，所有源文件都是utf8带BOM的（不要纠结，就这样定了，目前来说这是最方便的方案了）。

命名习惯
---
1、Mgr类，都是singleton的。

一般来说，只有全局唯一的而且不依赖任何其他类生存的类才是Mgr类，对其他类有依赖关系的，特别是对其他非singleton类有依赖关系的，都不应该是Mgr类

2、生成对象的几种常用接口的差别

*new* 表示仅仅产生对象，但并不会管理该对象，需要自己手动管理对象

*add* 表示产生对象并会管理该对象，外部不需要过多的维护对象的生存周期

设计概要
---
下面是一个简单的设计类图，使用[UMLer](http://uml.riaoo.com/)绘制，源文件在docs下。

![设计简图](https://github.com/zhs007/sanguo/blob/master/docs/uml001.jpg?raw=true “设计简图”)

其中，GameScene是游戏主体，一般来说，这个类是Scene的一个实例，随着游戏场景产生，并随着游戏场景而释放，不是一个全局类，所以需要保证所有的内存能被释放掉。

PersonMgr是全局的角色管理类，Singleton的实现，全局的静态表数据也是这里读取管理的。

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