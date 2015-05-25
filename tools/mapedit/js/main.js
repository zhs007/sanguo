/**
 * Created by zhs007 on 15/5/25.
 */

var frCanvas;

$(document).ready(function() {
    frCanvas = FrCanvas.create("editorCanvas");
    frSprite = FrSprite.create('res/worldmap.jpg');
    frCanvas.curScene.addChild(frSprite);

    setInterval(function () {
        frCanvas.onIdle();
    });


    //frCanvas.ok();
    //var c = document.getElementById("editorCanvas");
    //var cxt = c.getContext("2d");
    //cxt.fillStyle = "#FFFF00";
    //cxt.fillRect(0,0,150,75);

    //var s0 = Object.create(Sprite);
    //var s1 = Object.create(Sprite);
});