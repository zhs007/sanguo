/**
 * Created by zhs007 on 15/5/25.
 */

var SM_ScreenRect = {
    create: function () {
        var obj = FrDraw.create();

        obj.w = 100;
        obj.h = 100;

        obj.onDraw = SM_ScreenRect.onDraw;

        return obj;
    },

    onDraw: function (frCanvas) {
        frCanvas.strokeRect('#ffff00', 2, this._x, this._y, this.w, this.h);
    }
};

var LayerSmallMap = {
    create: function (frCanvas) {
        var layer = FrLayer.create('smallLayer', 100, frCanvas.frCtrl);

        layer.onTouchBegin = LayerSmallMap.onTouchBegin;
        layer.onTouchMove = LayerSmallMap.onTouchMove;
        layer.onTouchEnd = LayerSmallMap.onTouchEnd;
        layer.onTouchCancel = LayerSmallMap.onTouchCancel;
        layer.setEnableTouch(true);

        layer.updScreenRect = LayerSmallMap.updScreenRect;

        layer.screenRect = SM_ScreenRect.create();

        layer.imgBack = FrSprite.create('res/worldmap.jpg', function () {
            if (layer.imgBack.curFrame.width >= layer.imgBack.curFrame.height) {
                layer.imgBack.curFrame.dw = 256;
                layer.imgBack.curFrame.dh = 256 * layer.imgBack.curFrame.height / layer.imgBack.curFrame.width;
            }
            else {
                layer.imgBack.curFrame.dh = 256;
                layer.imgBack.curFrame.dw = 256 * layer.imgBack.curFrame.width / layer.imgBack.curFrame.height;
            }

            layer.updScreenRect();

            frCanvas.canvas.width = layer.imgBack.curFrame.dw;
            frCanvas.canvas.height = layer.imgBack.curFrame.dh;

            frCanvas.canvas.style.width = frCanvas.canvas.width + 'px';
            frCanvas.canvas.style.height = frCanvas.canvas.height + 'px';
        });

        layer.addChild(layer.imgBack);
        layer.addChild(layer.screenRect);

        return layer;
    },

    updScreenRect: function () {
        if (this.imgBack.img.complete) {
            this.screenRect.w = document.documentElement.clientWidth * this.imgBack.curFrame.dw / this.imgBack.curFrame.width;
            this.screenRect.h = document.documentElement.clientHeight * this.screenRect.w / document.body.clientWidth;

            var app = MapEditor.singleton;

            this.screenRect.setPosition(-app.layer.imgBack._x * this.screenRect.w / document.body.clientWidth,
                -app.layer.imgBack._y * this.screenRect.w / document.body.clientWidth);
            //this.screenRect.x = -app.layer.imgBack.x * this.screenRect.w / document.body.clientWidth;
            //this.screenRect.y = -app.layer.imgBack.y * this.screenRect.w / document.body.clientWidth;
        }
    },

    onTouchBegin: function (event) {
        return true;
    },

    onTouchMove: function (event) {
        //this.imgBack.x += (event.ox);
        //this.imgBack.y += (event.oy);

        this.screenRect.setPosition(this.screenRect._x + event.ox, this.screenRect._y + event.oy);
        //this.screenRect.x += (event.ox);
        //this.screenRect.y += (event.oy);

        var app = MapEditor.singleton;

        app.layer.imgBack.setPosition(-this.screenRect._x * app.layer.imgBack.curFrame.width / this.imgBack.curFrame.dw,
            -this.screenRect._y * app.layer.imgBack.curFrame.height / this.imgBack.curFrame.dh);
        //app.layer.imgBack.x = -this.screenRect.x * app.layer.imgBack.curFrame.width / this.imgBack.curFrame.dw;
        //app.layer.imgBack.y = -this.screenRect.y * app.layer.imgBack.curFrame.height / this.imgBack.curFrame.dh;

        //this.screenRect.x = -app.layer.imgBack.x * this.screenRect.w / document.body.clientWidth;
        //this.screenRect.y = -app.layer.imgBack.y * this.screenRect.w / document.body.clientWidth;
    },

    onTouchEnd: function (event) {
    },

    onTouchCancel: function (event) {
    }
};

var LayerUI = {
    create: function (frCanvas) {
        var layer = FrLayer.create('uiLayer', 2, frCanvas.frCtrl);

        layer.__proto__ = LayerUI;

        layer.setEnableTouch(true);
        layer.isFullScreen = true;

        layer.img1 = FrSprite.create('res/city001.png', function () { layer.onResize(); });
        layer.addChild(layer.img1);
        //layer.img1.x = 100;
        //layer.img1.y = 100;
        layer.img1.setCanTap(true, LayerUI.onTapImg1, layer);

        layer.img2 = FrSprite.create('res/city002.png', function () { layer.onResize(); });
        layer.addChild(layer.img2);
        //layer.img2.x = 300;
        //layer.img2.y = 100;
        layer.img2.setCanTap(true, LayerUI.onTapImg2, layer);

        return layer;
    },

    onTapImg1: function () {
        console.trace('onTapImg1');

        MapEditor.singleton.layer.setCurCity(1);

        return true;
    },

    onTapImg2: function () {
        console.trace('onTapImg2');

        MapEditor.singleton.layer.setCurCity(2);

        return true;
    },

    onResize: function () {
        if (this.img1.img.complete) {
            this.img1.setPosition(0, document.documentElement.clientHeight - this.img1.h);
            //this.img1.x = 0;
            //this.img1.y = document.documentElement.clientHeight - this.img1.h;
        }

        if (this.img2.img.complete && this.img1.img.complete) {
            this.img2.setPosition(this.img1.w, document.documentElement.clientHeight - this.img2.h);
            //this.img2.x = this.img1.w;
            //this.img2.y = document.documentElement.clientHeight - this.img1.h;
        }
    }
};

LayerUI.__proto__ = FrLayer;

var LayerMap = {
    create: function (frCanvas) {
        var layer = FrLayer.create('mainLayer', 1, frCanvas.frCtrl);

        layer.__proto__ = LayerMap;
        //layer.onTouchBegin = LayerMap.onTouchBegin;
        //layer.onTouchMove = LayerMap.onTouchMove;
        //layer.onTouchEnd = LayerMap.onTouchEnd;
        //layer.onTouchCancel = LayerMap.onTouchCancel;

        layer.setEnableTouch(true);

        var imgBack = FrSprite.create('res/worldmap.jpg');
        layer.addChild(imgBack);

        layer.imgBack = imgBack;

        layer.curSelCity = 0;
        layer.lstCity = [];

        return layer;
    },

    setCurCity: function (cityid) {
        this.curSelCity = cityid;
    },

    addCity: function (xx, yy) {
        if (this.curSelCity >= 1 && this.curSelCity <= 2) {
            var imgName = 'res/city00' + this.curSelCity + '.png';
            var img = FrSprite.create(imgName);
            this.imgBack.addChild(img);
            this.lstCity.push(img);

            img.setPosition(xx, yy);
            //img.x = xx;
            //img.y = yy;
        }
    },

    onTouchBegin: function (event) {
        return true;
    },

    onTouchMove: function (event) {
        this.imgBack.setPosition(this.imgBack._x + event.ox, this.imgBack._y + event.oy);
        //this.imgBack.x += (event.ox);
        //this.imgBack.y += (event.oy);

        MapEditor.singleton.layerSmall.updScreenRect();
    },

    onTouchEnd: function (event) {
        if (event.ox == 0 && event.oy == 0) {
            this.addCity(event.x, event.y);
        }
    },

    onTouchCancel: function (event) {
    }
};

LayerMap.__proto__ = FrLayer;

var MapEditor = {
    singleton: undefined,

    init: function (nameCanvas) {
        if (MapEditor.singleton != undefined) {
            return singleton;
        }

        var app = FrApplication.create();

        app.canvas = FrCanvas.create("editorCanvas");
        app.layer = LayerMap.create(app.canvas);
        app.canvas.curScene.addChild(app.layer);
        app.uiLayer = LayerUI.create(app.canvas);
        app.canvas.curScene.addChild(app.uiLayer);

        app.canvasSmall = FrCanvas.create("smallCanvas");
        app.layerSmall = LayerSmallMap.create(app.canvasSmall);
        app.canvasSmall.curScene.addChild(app.layerSmall);

        app.onIdle = MapEditor.onIdle;

        setInterval(function () { app.onIdle(); });

        MapEditor.singleton = app;

        window.onresize = MapEditor.onResize;
        MapEditor.onResize();

        return app;
    },

    onIdle: function () {
        this.canvas.onIdle();
        this.canvasSmall.onIdle();

        var status = document.getElementById('status');
        status.innerHTML = 'FPS:' + this.canvas.lastFPS + ' refurbish:' + this.canvas.curScene.curFrames;
    },

    onResize: function () {
        var app = MapEditor.singleton;

        document.body.style.overflow = 'hidden';
        app.canvas.canvas.width = document.documentElement.clientWidth;
        app.canvas.canvas.height = document.documentElement.clientHeight;

        var bx = document.documentElement.clientWidth - app.canvasSmall.canvas.width;
        app.canvasSmall.canvas.style.left = bx + 'px';

        app.layerSmall.updScreenRect();
        app.uiLayer.onResize();
        //document.body.style.overflow = 'hidden';
    }
};

//var frCanvas;

$(document).ready(function() {
    MapEditor.init('editorCanvas');
});