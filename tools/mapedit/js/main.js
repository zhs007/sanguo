/**
 * Created by zhs007 on 15/5/25.
 */

var LayerMapEditor = {
    create: function () {
        var layer = FrLayer.create();

        var imgBack = FrSprite.create('res/worldmap.jpg');
        layer.addChild(imgBack);

        return layer;
    }
}

var MapEditor = {
    create: function (nameCanvas) {
        var app = FrApplication.create();

        app.canvas = FrCanvas.create("editorCanvas");
        app.layer = LayerMapEditor.create();

        app.canvas.curScene.addChild(app.layer);

        app.onIdle = MapEditor.onIdle;

        setInterval(function () { app.onIdle(); });

        return app;
    },

    onIdle: function () {
        this.canvas.onIdle();

        var status = document.getElementById('status');
        status.innerHTML = 'FPS:' + this.canvas.curScene.lastFPS;
    }
};

//var frCanvas;

$(document).ready(function() {
    var app = MapEditor.create('editorCanvas');
});