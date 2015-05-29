/**
 * Frozen
 * a extremely simple html5 canvas engine.
 */

var FrSpriteFrame = {
    create: function (bx, by, w, h) {
        var obj = {};

        obj.bx = bx;
        obj.by = by;
        obj.width = w;
        obj.height = h;
        obj.dw = w;
        obj.dh = h;

        return obj;
    }
};

var FrNode = {
    create: function () {
        var obj = {};

        obj._lstChild = [];

        obj.__proto__ = FrNode;

        obj._frCanvas = undefined;

        //! 相对父节点的坐标
        obj._x = 0;
        obj._y = 0;

        //! 绝对坐标
        //! 绝对坐标并不是实时维护的，在渲染的时候
        //! 如果父节点的需要刷新，子节点才需要刷新
        //! 如果本轮已经改变过相对坐标，也需要刷新
        obj._clientX = 0;
        obj._clientY = 0;
        obj._isNeedUpdClientXY = false;

        //! 宽度和高度
        obj.w = 0;
        obj.h = 0;

        //! 显示区域，如果没有设这个，表示不会显示一部分
        //! top、left、width、height
        obj._scrollRect = undefined;

        obj.isFullScreen = false;   //! 如果是全屏节点，isIn的时候必然返回true
        obj.zOrder = 0;

        obj._canTap = false;
        obj._funcTap = undefined;
        obj._funcTapThis = undefined;
        obj._tapDownChild = undefined;   //! 如果有子节点处理了TapDown事件，这个就是那个子节点

        obj.parent = undefined;

        return obj;
    },

    setPosition: function (xx, yy) {
        this._x = xx;
        this._y = yy;

        this._isNeedUpdClientXY = true;

        this.setFrCanvasRefutbish();
    },

    setScrollRect: function (x, y, w, h) {
        if (this._scrollRect == undefined) {
            this._scrollRect = {left: x, top: y, width: w, height: h};
        }
        else {
            this._scrollRect.left = x;
            this._scrollRect.top = y;
            this._scrollRect.width = w;
            this._scrollRect.height = h;
        }

        this.setFrCanvasRefutbish();
    },

    clearScrollRect: function () {
        this._scrollRect = undefined;

        this.setFrCanvasRefutbish();
    },

    addChild: function (nodeChild) {
        if (nodeChild.parent != undefined) {
            return ;
        }

        nodeChild._isNeedUpdClientXY = true;

        nodeChild.parent = this;

        this._lstChild.push(nodeChild);

        if (this._frCanvas != undefined) {
            nodeChild.setFrCanvas(this._frCanvas);

            this._frCanvas.isNeedRefurbish = true;
        }
    },

    removeChild: function (nodeChild) {
        if (nodeChild.parent == this) {
            nodeChild._isNeedUpdClientXY = true;

            this._lstChild.split(nodeChild);
            nodeChild.parent = undefined;

            if (this._frCanvas != undefined) {
                nodeChild.clearFrCanvas();

                this._frCanvas.isNeedRefurbish = true;
            }
        }
    },

    isIn: function (xx, yy) {
        if (this.isFullScreen) {
            return true;
        }

        return xx >= this._x && xx < this._x + this.w && yy >= this._y && yy < this._y + this.h;
    },

    setCanTap: function (canTap, funcTap, funcTapThis) {
        this._canTap = canTap;

        //! 如果是允许点击，一直向上遍历到FrLayer，全部节点都设置为canTap
        if (canTap) {
            if (funcTap != undefined) {
                this._funcTap = funcTap;
            }

            if (funcTapThis != undefined) {
                this._funcTapThis = funcTapThis;
            }

            var p = this.parent;
            if (p != undefined) {
                if (p.isFrLayer == undefined || !p.isFrLayer()) {
                    p.setCanTap(true, undefined, undefined);
                }
                else {
                    p._canTap = true;
                }
            }
        }
    },

    procTap: function (isDown, downx, downy, upx, upy) {
        if (this._funcTap != undefined) {
            if (this._funcTap.call(this._funcTapThis, isDown, downx, downy, upx, upy)) {
                return true;
            }
        }

        if (!isDown) {
            if (this._tapDownChild != undefined) {
                this._tapDownChild.procTap(isDown, downx, downy, upx, upy);

                return true;
            }

            return false;
        }

        var frNodeThis = this;
        this.forEachChild(function (frNode) {
            if (frNode._canTap && frNode.isIn(event.x, event.y)) {
                if (frNode.procTap(isDown, downx, downy, upx, upy)) {
                    frNodeThis._tapDownChild = frNode;

                    return true;
                }
            }

            return false;
        });

        return false;
    },

    render: function () {
        if (this.parent != undefined) {
            if (this.parent._isNeedUpdClientXY) {
                this._isNeedUpdClientXY = true;
            }

            if (this._isNeedUpdClientXY) {
                this._clientX = this.parent._clientX + this._x;
                this._clientY = this.parent._clientY + this._y;
            }
        }
        else {
            if (this._isNeedUpdClientXY) {
                this._clientX = this._x;
                this._clientY = this._y;
            }
        }

        this.onRender();

        this.forEachChild(function (frNode) {
            frNode.render();

            return false;
        });

        this._isNeedUpdClientXY = false;
    },

    onRender: function () {
    },

    forEachChild: function (func) {
        for (var i = 0; i < this._lstChild.length; ++i) {
            if (func(this._lstChild[i])) {
                return ;
            }
        }
    },

    setFrCanvas: function (frCanvas) {
        this._frCanvas = frCanvas;
        this.forEachChild(function (frNode) {
            frNode.setFrCanvas(frCanvas);
        });
    },

    clearFrCanvas: function () {
        this._frCanvas = undefined;
        this.forEachChild(function (frNode) {
            frNode.clearFrCanvas();
        });
    },

    setFrCanvasRefutbish: function () {
        if (this._frCanvas != undefined) {
            this._frCanvas.isNeedRefurbish = true;
        }
    }
};

var FrDraw = {
    create: function () {
        var obj = FrNode.create();

        obj.__proto__ = FrDraw;

        obj.onDraw = undefined;

        return obj;
    },

    onRender: function () {
        if (this.onDraw != undefined) {
            this.onDraw(this._frCanvas);
        }
    }
};

FrDraw.__proto__ = FrNode;

var FrSprite = {
    create: function (imgName, onload) {
        var obj = FrNode.create();

        obj.__proto__ = FrSprite;

        obj.curFrame = undefined;

        obj.img = new Image();
        obj.img.onload = function () {
            obj.onLoadComplete();
            if (onload != undefined) {
                onload();
            }
        };
        obj.img.src = imgName;

        return obj;
    },

    onRender: function () {
        var frCanvas = this._frCanvas;
        if (this.img.complete && this.curFrame != undefined) {
            frCanvas.context.drawImage(this.img,
                this.curFrame.bx, this.curFrame.by, this.curFrame.width, this.curFrame.height,
                this._clientX, this._clientY, this.curFrame.dw, this.curFrame.dh);
        }
    },

    onLoadComplete: function () {
        if (this.img.complete) {
            if (this.curFrame == undefined) {
                this.curFrame = FrSpriteFrame.create(0, 0, this.img.width, this.img.height);

                this.w = this.img.width;
                this.h = this.img.height;

                this.setFrCanvasRefutbish();
            }
        }
    }
};

FrSprite.__proto__ = FrNode;

var FrScene = {
    create: function (frCanvas) {
        var obj = FrNode.create();

        obj.__proto__ = FrScene;

        obj.setFrCanvas(frCanvas);

        obj.curFrames = 0;

        return obj;
    },

    onRender: function () {
        this.curFrames += 1;
    }
};

FrScene.__proto__ = FrNode;

var FrCtrl = {
    create: function (objMain) {
        var obj = {};

        obj.lstTouches = [];
        obj.lstListener = [];
        obj.objMain = objMain;

        obj.addListener = FrCtrl.addListener;
        obj.removeListener = FrCtrl.removeListener;

        obj.onTouchStart = FrCtrl.onTouchStart;
        obj.onTouchMove = FrCtrl.onTouchMove;
        obj.onTouchEnd = FrCtrl.onTouchEnd;
        obj.onTouchCancel = FrCtrl.onTouchCancel;

        obj.onMouseDown = FrCtrl.onMouseDown;
        obj.onMouseMove = FrCtrl.onMouseMove;
        obj.onMouseUp = FrCtrl.onMouseUp;

        objMain.addEventListener('touchstart', function (event) { obj.onTouchStart(event); }, false);
        objMain.addEventListener('touchmove', function (event) { obj.onTouchMove(event); }, false);
        objMain.addEventListener('touchend', function (event) { obj.onTouchEnd(event); }, false);
        objMain.addEventListener('touchcancel', function (event) { obj.onTouchCancel(event); }, false);

        objMain.addEventListener('mousedown', function (event) { obj.onMouseDown(event); }, false);
        objMain.addEventListener('mousemove', function (event) { obj.onMouseMove(event); }, false);
        objMain.addEventListener('mouseup', function (event) { obj.onMouseUp(event); }, false);

        return obj;
    },

    addListener: function (id, listener, order) {
        if (order == undefined) {
            order = 0;
        }

        this.lstListener.push({id: id, func: listener, isBegin: false, zOrder: order});
        this.lstListener.sort(function (a, b) {
            return b.zOrder - a.zOrder;
        });
    },

    removeListener: function (id) {
        for (var i = 0; i < this.lstListener.length; ++i) {
            var listener = this.lstListener[i];
            if (listener.id == id) {
                this.lstListener.splice(i, 1);

                break;
            }
        }

        this.lstListener.sort(function (a, b) {
            return b.zOrder - a.zOrder;
        });
    },

    onTouchStart: function (event) {
        var frCtrl = this;

        for (var i = 0; i < event.touches.length; ++i) {
            var it = event.touches[i];
            var t = { bx: it.clientX, by: it.clientY, x: it.clientX, y: it.clientY, ox: 0, oy: 0 };

            frCtrl.lstTouches[it.identifier] = t;
        }

        for (var i = 0; i < frCtrl.lstListener.length; ++i) {
            var listener = frCtrl.lstListener[i];
            if (listener.func.onTouchBegin != undefined) {
                if (listener.func.onTouchBegin(frCtrl.lstTouches[0])) {
                    listener.isBegin = true;
                    break;
                }
            }
        }
    },

    onTouchMove: function (event) {
        var frCtrl = this;

        for (var i = 0; i < event.touches.length; ++i) {
            var it = event.touches[i];

            frCtrl.lstTouches[it.identifier].ox = it.clientX - frCtrl.lstTouches[it.identifier].x;
            frCtrl.lstTouches[it.identifier].oy = it.clientY - frCtrl.lstTouches[it.identifier].y;

            frCtrl.lstTouches[it.identifier].x = it.clientX;
            frCtrl.lstTouches[it.identifier].y = it.clientY;
        }

        for (var i = 0; i < frCtrl.lstListener.length; ++i) {
            var listener = frCtrl.lstListener[i];
            if (listener.isBegin && listener.func.onTouchMove != undefined) {
                listener.func.onTouchMove(frCtrl.lstTouches[0]);
            }
        }
    },

    onTouchEnd: function (event) {
        var frCtrl = this;

        for (var i = 0; i < event.touches.length; ++i) {
            var it = event.touches[i];

            frCtrl.lstTouches[it.identifier].ox = it.clientX - frCtrl.lstTouches[it.identifier].x;
            frCtrl.lstTouches[it.identifier].oy = it.clientY - frCtrl.lstTouches[it.identifier].y;

            frCtrl.lstTouches[it.identifier].x = it.clientX;
            frCtrl.lstTouches[it.identifier].y = it.clientY;
        }

        for (var i = 0; i < frCtrl.lstListener.length; ++i) {
            var listener = frCtrl.lstListener[i];
            if (listener.isBegin && listener.func.onTouchEnd != undefined) {
                listener.func.onTouchEnd(frCtrl.lstTouches[0]);
                listener.isBegin = false;
            }
        }
    },

    onTouchCancel: function (event) {
        var frCtrl = this;

        for (var i = 0; i < frCtrl.lstListener.length; ++i) {
            var listener = frCtrl.lstListener[i];
            if (listener.isBegin && listener.func.onTouchCancel != undefined) {
                listener.func.onTouchCancel(frCtrl.lstTouches[0]);
                listener.isBegin = false;
            }
        }
    },

    onMouseDown: function (event) {
        var t = { bx: event.clientX, by: event.clientY, x: event.clientX, y: event.clientY, ox: 0, oy: 0 };
        var frCtrl = this;
        frCtrl.lstTouches.push(t);

        for (var i = 0; i < frCtrl.lstListener.length; ++i) {
            var listener = frCtrl.lstListener[i];
            if (listener.func.onTouchBegin != undefined) {
                if (listener.func.onTouchBegin(t)) {
                    listener.isBegin = true;
                    break;
                }
            }
        }
    },

    onMouseMove: function (event) {
        var frCtrl = this;
        if (frCtrl.lstTouches.length <= 0) {
            return ;
        }

        var t = frCtrl.lstTouches[0];

        t.ox = event.clientX - t.x;
        t.oy = event.clientY - t.y;
        t.x = event.clientX;
        t.y = event.clientY;

        for (var i = 0; i < frCtrl.lstListener.length; ++i) {
            var listener = frCtrl.lstListener[i];
            if (listener.isBegin && listener.func.onTouchMove != undefined) {
                listener.func.onTouchMove(t);
            }
        }
    },

    onMouseUp: function (event) {
        var frCtrl = this;
        if (frCtrl.lstTouches.length <= 0) {
            return ;
        }

        var t = frCtrl.lstTouches[0];

        t.ox = event.clientX - t.bx;
        t.oy = event.clientY - t.by;
        t.x = event.clientX;
        t.y = event.clientY;

        for (var i = 0; i < frCtrl.lstListener.length; ++i) {
            var listener = frCtrl.lstListener[i];
            if (listener.isBegin && listener.func.onTouchEnd != undefined) {
                listener.func.onTouchEnd(t);
                listener.isBegin = false;
            }
        }

        frCtrl.lstTouches.splice(0, frCtrl.lstTouches.length);
    }
};

var FrLayer = {
    create: function (idName, zOrder, frCtrl) {
        var obj = FrNode.create();

        obj.__proto__ = FrLayer;

        obj.idName = idName;
        obj.zOrder = zOrder;
        obj.frCtrl = frCtrl;
        obj.isEnableTouch = false;

        return obj;
    },

    setEnableTouch: function (isEnable) {
        this.isEnableTouch = isEnable;

        var frCtrl = this.frCtrl;

        if (isEnable) {
            frCtrl.addListener(this.idName, this, this.zOrder);
        }
        else {
            frCtrl.removeListener(this.idName);
        }
    },

    isFrLayer: function () {
        return true;
    },

    onTouchBegin: function (event) {
        if (!this.isEnableTouch) {
            return false;
        }

        if (this._canTap) {
            if (this.isIn(event.x, event.y)) {
                if (this.procTap(true, event.x, event.y, event.x, event.y)) {
                    return true;
                }
            }
        }

        return false;
    },

    onTouchMove: function (event) {
    },

    onTouchEnd: function (event) {
        if (!this.isEnableTouch) {
            return ;
        }

        if (this._canTap) {
            if (this.isIn(event.x, event.y)) {
                this.procTap(false, event.bx, event.by, event.x, event.y);
            }
        }
    },

    onTouchCancel: function (event) {
        if (!this.isEnableTouch) {
            return ;
        }

        if (this._canTap) {
            if (this.isIn(event.bx, event.by)) {
                this.procTap(false, event.bx, event.by, -1, -1);
            }
        }
    }
};

FrLayer.__proto__ = FrNode;

var FrCanvas = {
    create: function (nameCanvas) {
        var obj = {};

        obj.__proto__ = FrCanvas;

        obj.canvas = document.getElementById(nameCanvas);
        obj.context = obj.canvas.getContext('2d');

        obj.frCtrl = FrCtrl.create(obj.canvas);

        obj.isNeedRefurbish = false;

        obj.lastTimestamp = 0;
        obj.curFrames = 0;
        obj.lastSecond = 0;
        obj.lastFPS = 0;

        obj.curScene = FrScene.create(obj);

        return obj;
    },

    fillRect: function (sc, fc, lw, x, y, w, h) {
        this.context.fillStyle = fc;
        this.context.strokeStyle = sc;
        this.context.lineWidth = lw;
        this.context.fillRect(x, y, w, h);
    },

    strokeRect: function (sc, lw, x, y, w, h) {
        this.context.strokeStyle = sc;
        this.context.lineWidth = lw;
        this.context.strokeRect(x, y, w, h);
    },

    onIdle: function () {
        var d1 = new Date();
        var ts1 = d1.getTime();

        if (this.curFrames == 0) {
            this.lastSecond = ts1;
            this.curFrames = 1;
        }
        else {
            this.curFrames += 1;

            var off = ts1 - this.lastSecond;
            if (off >= 1000) {
                this.lastFPS = (this.curFrames * 1000 / off).toFixed(2);
                this.lastSecond += 1000;
                this.curFrames = 1;
            }
        }

        if (this.isNeedRefurbish) {
            this.context.clearRect(0, 0, this.canvas.width, this.canvas.height);
            this.curScene.render();

            this.isNeedRefurbish = false;
        }

        var d2 = new Date();
        var ts2 = d2.getTime();

        this.lastTimestamp = ts2 - ts1;
    }
};

var FrApplication = {
    create: function () {
        var obj = {};

        return obj;
    }
};