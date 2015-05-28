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

        obj.lstChild = [];

        obj.__proto__ = FrNode;

        obj.x = 0;
        obj.y = 0;
        obj.w = 0;
        obj.h = 0;

        obj.isFullScreen = false;   //! 如果是全屏节点，isIn的时候必然返回true
        obj.zOrder = 0;

        obj.canTap = false;
        obj._funcTap = undefined;
        obj._funcTapThis = undefined;
        obj._tapDownChild = undefined;   //! 如果有子节点处理了TapDown事件，这个就是那个子节点

        obj.parent = undefined;

        return obj;
    },

    addChild: function (nodeChild) {
        if (nodeChild.parent != undefined) {
            return ;
        }

        nodeChild.parent = this;

        this.lstChild.push(nodeChild);
    },

    removeChild: function (nodeChild) {
        if (nodeChild.parent == this) {
            this.lstChild.split(nodeChild);
            nodeChild.parent = undefined;
        }
    },

    isIn: function (xx, yy) {
        if (this.isFullScreen) {
            return true;
        }

        return xx >= this.x && xx < this.x + this.w && yy >= this.y && yy < this.y + this.h;
    },

    setCanTap: function (canTap, funcTap, funcTapThis) {
        this.canTap = canTap;

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
                    p.canTap = true;
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

        for (var i = 0; i < this.lstChild.length; ++i) {
            var n = this.lstChild[i];
            if (n.canTap && n.isIn(event.x, event.y)) {
                if (n.procTap(isDown, downx, downy, upx, upy)) {
                    this._tapDownChild = n;

                    return true;
                }
            }
        }

        return false;
    },

    onRender: function (frCanvas) {
        for (var i = 0; i < this.lstChild.length; ++i) {
            this.lstChild[i].onRender(frCanvas);
        }
    }
};

var FrDraw = {
    create: function () {
        var obj = FrNode.create();

        obj.onDraw = undefined;

        obj.__proto__ = FrDraw;

        return obj;
    },

    onRender: function (frCanvas) {
        if (this.onDraw != undefined) {
            this.onDraw(frCanvas);
        }

        FrNode.onRender.call(this, frCanvas);
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

    onRender: function (frCanvas) {
        if (this.img.complete && this.curFrame != undefined) {
            frCanvas.context.drawImage(this.img,
                this.curFrame.bx, this.curFrame.by, this.curFrame.width, this.curFrame.height,
                this.x, this.y, this.curFrame.dw, this.curFrame.dh);
        }

        FrNode.onRender.call(this, frCanvas);
    },

    onLoadComplete: function () {
        if (this.img.complete) {
            if (this.curFrame == undefined) {
                this.curFrame = FrSpriteFrame.create(0, 0, this.img.width, this.img.height);

                this.w = this.img.width;
                this.h = this.img.height;
            }
        }
    }
};

FrSprite.__proto__ = FrNode;

var FrScene = {
    create: function () {
        var obj = FrNode.create();

        obj.lastTimestamp = 0;
        obj.curFrames = 0;
        obj.lastSecond = 0;
        obj.lastFPS = 0;

        obj.__proto__ = FrScene;

        return obj;
    },

    onRender: function (frCanvas) {
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

        FrNode.onRender.call(this, frCanvas);

        var d2 = new Date();
        var ts2 = d2.getTime();

        this.lastTimestamp = ts2 - ts1;
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

        for (var i = 0; i < frCtrl.lstListener.length; ++i) {
            var listener = frCtrl.lstListener[i];
            if (listener.func.onTouchBegin != undefined) {
                if (listener.func.onTouchBegin()) {
                    listener.isBegin = true;
                    break;
                }
            }
        }
    },

    onTouchMove: function (event) {
        var frCtrl = this;

        for (var i = 0; i < frCtrl.lstListener.length; ++i) {
            var listener = frCtrl.lstListener[i];
            if (listener.isBegin && listener.func.onTouchMove != undefined) {
                listener.func.onTouchMove();
            }
        }
    },

    onTouchEnd: function (event) {
        var frCtrl = this;

        for (var i = 0; i < frCtrl.lstListener.length; ++i) {
            var listener = frCtrl.lstListener[i];
            if (listener.isBegin && listener.func.onTouchEnd != undefined) {
                listener.func.onTouchEnd();
                listener.isBegin = false;
            }
        }
    },

    onTouchCancel: function (event) {
        var frCtrl = this;

        for (var i = 0; i < frCtrl.lstListener.length; ++i) {
            var listener = frCtrl.lstListener[i];
            if (listener.isBegin && listener.func.onTouchCancel != undefined) {
                listener.func.onTouchCancel();
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

        t.ox = event.clientX - t.x;
        t.oy = event.clientY - t.y;
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

        if (this.canTap) {
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

        if (this.canTap) {
            if (this.isIn(event.x, event.y)) {
                this.procTap(false, event.bx, event.by, event.x, event.y);
            }
        }
    },

    onTouchCancel: function (event) {
        if (!this.isEnableTouch) {
            return ;
        }

        if (this.canTap) {
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

        obj.canvas = document.getElementById(nameCanvas);
        obj.context = obj.canvas.getContext('2d');

        obj.curScene = FrScene.create();
        obj.frCtrl = FrCtrl.create(obj.canvas);

        obj.fillRect = FrCanvas.fillRect;
        obj.strokeRect = FrCanvas.strokeRect;

        obj.onIdle = FrCanvas.onIdle;

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
        this.context.clearRect(0, 0, this.canvas.width, this.canvas.height);
        this.curScene.onRender(this);
    }
};

var FrApplication = {
    create: function () {
        var obj = {};

        return obj;
    }
};