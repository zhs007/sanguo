/**
 * Created by zhs007 on 15/5/25.
 */

var LayerMapEditor = {
    create: function () {
        var layer = FrLayer.create();

        layer.onTouchBegin = LayerMapEditor.onTouchBegin;
        layer.onTouchMove = LayerMapEditor.onTouchMove;
        layer.onTouchEnd = LayerMapEditor.onTouchEnd;
        layer.onTouchCancel = LayerMapEditor.onTouchCancel;

        layer.setEnableTouch(true);

        var imgBack = FrSprite.create('res/worldmap.jpg');
        layer.addChild(imgBack);

        layer.imgBack = imgBack;

        return layer;
    },

    onTouchBegin: function (event) {
        //console.log('onMouseDown');
    },

    onTouchMove: function (event) {
        this.imgBack.x += (event.ox);
        this.imgBack.y += (event.oy);
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
        app.layer = LayerMapEditor.create();

        app.canvas.curScene.addChild(app.layer);

        app.onIdle = MapEditor.onIdle;

        setInterval(function () { app.onIdle(); });

        MapEditor.singleton = app;

        window.onresize = MapEditor.onResize;
        MapEditor.onResize();

        return app;
    },

    onIdle: function () {
        this.canvas.onIdle();

        //var status = document.getElementById('status');
        //status.innerHTML = 'FPS:' + this.canvas.curScene.lastFPS;
    },

    onResize: function () {
        var app = MapEditor.singleton;

        document.body.style.overflow = 'hidden';
        app.canvas.canvas.width = document.body.clientWidth;
        app.canvas.canvas.height = document.body.clientHeight;
        //document.body.style.overflow = 'hidden';
    }
};

//var frCanvas;

$(document).ready(function() {
    MapEditor.init('editorCanvas');
});