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

        obj.addChild = FrNode.addChild;
        obj.onRender = FrNode.onRender;

        obj.x = 0;
        obj.y = 0;

        return obj;
    },

    addChild: function (nodeChild) {
        this.lstChild.push(nodeChild);
    },

    onRender: function (canvas) {
        for (var i = 0; i < this.lstChild.length; ++i) {
            this.lstChild[i].onRender(canvas);
        }
    }
};

var FrDraw = {
    create: function () {
        var obj = FrNode.create();

        obj.onDraw = undefined;

        obj.onRender_FrNode = obj.onRender;
        obj.onRender = FrDraw.onRender;

        return obj;
    },

    onRender: function (canvas) {
        if (this.onDraw != undefined) {
            this.onDraw(canvas);
        }

        this.onRender_FrNode(canvas);
    }
};

var FrSprite = {
    create: function (imgName, onload) {
        var obj = FrNode.create();

        obj.onLoadComplete = FrSprite.onLoadComplete;
        obj.curFrame = undefined;

        obj.img = new Image();
        obj.img.onload = function () {
            obj.onLoadComplete();
            if (onload != undefined) {
                onload();
            }
        };
        obj.img.src = imgName;

        obj.onRender_FrNode = obj.onRender;
        obj.onRender = FrSprite.onRender;

        return obj;
    },

    onRender: function (canvas) {
        if (this.img.complete && this.curFrame != undefined) {
            canvas.context.drawImage(this.img,
                this.curFrame.bx, this.curFrame.by, this.curFrame.width, this.curFrame.height,
                this.x, this.y, this.curFrame.dw, this.curFrame.dh);
        }

        this.onRender_FrNode(canvas);
    },

    onLoadComplete: function () {
        if (this.img.complete) {
            if (this.curFrame == undefined) {
                this.curFrame = FrSpriteFrame.create(0, 0, this.img.width, this.img.height);
            }
        }
    }
};

var FrScene = {
    create: function () {
        var obj = FrNode.create();

        obj.lastTimestamp = 0;
        obj.curFrames = 0;
        obj.lastSecond = 0;
        obj.lastFPS = 0;

        obj.onRender_FrNode = obj.onRender;
        obj.onRender = FrScene.onRender;

        return obj;
    },

    onRender: function (canvas) {
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

        this.onRender_FrNode(canvas);

        var d2 = new Date();
        var ts2 = d2.getTime();

        this.lastTimestamp = ts2 - ts1;
    }
};

var FrCtrl = {
    singleton: undefined,

    getSingleton: function () {
        if (FrCtrl.singleton != undefined) {
            return FrCtrl.singleton;
        }

        var objMain = document;
        var obj = {};

        obj.lstTouches = [];
        obj.lstListener = [];
        obj.objMain = objMain;

        obj.release = FrCtrl.release;
        obj.addListener = FrCtrl.addListener;
        obj.removeListener = FrCtrl.removeListener;

        objMain.addEventListener('touchstart', FrCtrl.onTouchStart, false);
        objMain.addEventListener('touchmove', FrCtrl.onTouchMove, false);
        objMain.addEventListener('touchend', FrCtrl.onTouchEnd, false);
        objMain.addEventListener('touchcancel', FrCtrl.onTouchCancel, false);

        objMain.addEventListener('mousedown', FrCtrl.onMouseDown, false);
        objMain.addEventListener('mousemove', FrCtrl.onMouseMove, false);
        objMain.addEventListener('mouseup', FrCtrl.onMouseUp, false);

        this.singleton = obj;

        return obj;
    },

    release: function () {
        var frCtrl = FrCtrl.singleton;
        var objMain = frCtrl.objMain;

        objMain.removeEventListener('touchstart', FrCtrl.onTouchStart, false);
        objMain.removeEventListener('touchmove', FrCtrl.onTouchMove, false);
        objMain.removeEventListener('touchend', FrCtrl.onTouchEnd, false);
        objMain.removeEventListener('touchcancel', FrCtrl.onTouchCancel, false);

        objMain.removeEventListener('mousedown', FrCtrl.onMouseDown, false);
        objMain.removeEventListener('mousemove', FrCtrl.onMouseMove, false);
        objMain.removeEventListener('mouseup', FrCtrl.onMouseUp, false);
    },

    addListener: function (listener) {
        this.lstListener.push(listener);
    },

    removeListener: function (listener) {
        this.lstListener.split(listener);
    },

    onTouchStart: function (event) {
        var frCtrl = FrCtrl.singleton;

        for (var i = 0; i < frCtrl.lstListener.length; ++i) {
            var listener = frCtrl.lstListener[i];
            if (listener.hasOwnProperty('onTouchBegin')) {
                listener.onTouchBegin();
            }
        }
    },

    onTouchMove: function (event) {
        var frCtrl = FrCtrl.singleton;

        for (var i = 0; i < frCtrl.lstListener.length; ++i) {
            var listener = frCtrl.lstListener[i];
            if (listener.hasOwnProperty('onTouchMove')) {
                listener.onTouchMove();
            }
        }
    },

    onTouchEnd: function (event) {
        var frCtrl = FrCtrl.singleton;

        for (var i = 0; i < frCtrl.lstListener.length; ++i) {
            var listener = frCtrl.lstListener[i];
            if (listener.hasOwnProperty('onTouchEnd')) {
                listener.onTouchEnd();
            }
        }
    },

    onTouchCancel: function (event) {
        var frCtrl = FrCtrl.singleton;

        for (var i = 0; i < frCtrl.lstListener.length; ++i) {
            var listener = frCtrl.lstListener[i];
            if (listener.hasOwnProperty('onTouchCancel')) {
                listener.onTouchCancel();
            }
        }
    },

    onMouseDown: function (event) {
        var t = { bx: event.clientX, by: event.clientY, x: event.clientX, y: event.clientY, ox: 0, oy: 0 };
        var frCtrl = FrCtrl.singleton;
        frCtrl.lstTouches.push(t);

        for (var i = 0; i < frCtrl.lstListener.length; ++i) {
            var listener = frCtrl.lstListener[i];
            if (listener.hasOwnProperty('onTouchBegin')) {
                listener.onTouchBegin(t);
            }
        }
    },

    onMouseMove: function (event) {
        var frCtrl = FrCtrl.singleton;
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
            if (listener.hasOwnProperty('onTouchMove')) {
                listener.onTouchMove(t);
            }
        }
    },

    onMouseUp: function (event) {
        var frCtrl = FrCtrl.singleton;
        var t = frCtrl.lstTouches[0];

        t.ox = event.clientX - t.x;
        t.oy = event.clientY - t.y;
        t.x = event.clientX;
        t.y = event.clientY;

        for (var i = 0; i < frCtrl.lstListener.length; ++i) {
            var listener = frCtrl.lstListener[i];
            if (listener.hasOwnProperty('onTouchEnd')) {
                listener.onTouchEnd(t);
            }
        }

        frCtrl.lstTouches.splice(0, frCtrl.lstTouches.length);
    }
};

var FrLayer = {
    create: function () {
        var obj = FrNode.create();

        obj.setEnableTouch = FrLayer.setEnableTouch;

        return obj;
    },

    setEnableTouch: function (isEnable) {
        var frCtrl = FrCtrl.singleton;

        if (isEnable) {
            frCtrl.addListener(this);
        }
        else {
            frCtrl.removeListener(this);
        }
    }
};

var FrCanvas = {
    create: function (nameCanvas) {
        var obj = {};

        obj.canvas = document.getElementById(nameCanvas);
        obj.context = obj.canvas.getContext('2d');

        obj.curScene = FrScene.create();
        obj.mgrCtrl = FrCtrl.getSingleton();

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