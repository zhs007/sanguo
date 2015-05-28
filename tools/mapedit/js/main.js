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
        frCanvas.strokeRect('#ffff00', 2, this.x, this.y, this.w, this.h);
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

            this.screenRect.x = -app.layer.imgBack.x * this.screenRect.w / document.body.clientWidth;
            this.screenRect.y = -app.layer.imgBack.y * this.screenRect.w / document.body.clientWidth;
        }
    },

    onTouchBegin: function (event) {
        return true;
    },

    onTouchMove: function (event) {
        //this.imgBack.x += (event.ox);
        //this.imgBack.y += (event.oy);

        this.screenRect.x += (event.ox);
        this.screenRect.y += (event.oy);

        var app = MapEditor.singleton;

        app.layer.imgBack.x = -this.screenRect.x * app.layer.imgBack.curFrame.width / this.imgBack.curFrame.dw;
        app.layer.imgBack.y = -this.screenRect.y * app.layer.imgBack.curFrame.height / this.imgBack.curFrame.dh;

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

        layer.setEnableTouch(true);
        layer.isFullScreen = true;

        layer.img1 = FrSprite.create('res/city001.png');
        layer.addChild(layer.img1);
        layer.img1.x = 100;
        layer.img1.y = 100;
        layer.img1.setCanTap(true, LayerUI.onTapImg1, layer);

        layer.img2 = FrSprite.create('res/city002.png');
        layer.addChild(layer.img2);
        layer.img2.x = 300;
        layer.img2.y = 100;
        layer.img2.setCanTap(true, LayerUI.onTapImg2, layer);

        return layer;
    },

    onTapImg1: function () {
        console.trace('onTapImg1');

        return true;
    },

    onTapImg2: function () {
        console.trace('onTapImg2');

        return true;
    }
};

var LayerMap = {
    create: function (frCanvas) {
        var layer = FrLayer.create('mainLayer', 1, frCanvas.frCtrl);

        layer.onTouchBegin = LayerMap.onTouchBegin;
        layer.onTouchMove = LayerMap.onTouchMove;
        layer.onTouchEnd = LayerMap.onTouchEnd;
        layer.onTouchCancel = LayerMap.onTouchCancel;

        layer.setEnableTouch(true);

        var imgBack = FrSprite.create('res/worldmap.jpg');
        layer.addChild(imgBack);

        layer.imgBack = imgBack;

        return layer;
    },

    onTouchBegin: function (event) {
        return true;
    },

    onTouchMove: function (event) {
        this.imgBack.x += (event.ox);
        this.imgBack.y += (event.oy);

        MapEditor.singleton.layerSmall.updScreenRect();
    },

    onTouchEnd: function (event) {
    },

    onTouchCancel: function (event) {
    }
}

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
        status.innerHTML = 'FPS:' + this.canvas.curScene.lastFPS;
    },

    onResize: function () {
        var app = MapEditor.singleton;

        document.body.style.overflow = 'hidden';
        app.canvas.canvas.width = document.documentElement.clientWidth;
        app.canvas.canvas.height = document.documentElement.clientHeight;

        var bx = document.documentElement.clientWidth - app.canvasSmall.canvas.width;
        app.canvasSmall.canvas.style.left = bx + 'px';

        app.layerSmall.updScreenRect();
        //document.body.style.overflow = 'hidden';
    }
};

//var frCanvas;

$(document).ready(function() {
    MapEditor.init('editorCanvas');
});