/**
 * Frozen
 * a extremely simple html5 canvas engine.
 */

var FrNode = {
    create: function () {
        var obj = {};

        obj.lstChild = [];

        obj.addChild = FrNode.addChild;
        obj.onRender = FrNode.onRender;

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

var FrSprite = {
    create: function (imgName) {
        var obj = FrNode.create();

        obj.img = new Image();
        obj.img.src = imgName;

        obj.onRender_FrNode = obj.onRender;
        obj.onRender = FrSprite.onRender;

        return obj;
    },

    onRender: function (canvas) {
        if (this.img.complete) {
            canvas.context.drawImage(this.img, 0, 0, this.img.width, this.img.height, 0, 0, this.img.width, this.img.height);
        }

        this.onRender_FrNode(canvas);
    }
};

var FrScene = {
    create: function () {
        var obj = FrNode.create();

        return obj;
    }
};

var FrCanvas = {
    create: function (nameCanvas) {
        var obj = {};

        obj.canvas = document.getElementById(nameCanvas);
        obj.context = obj.canvas.getContext('2d');

        obj.curScene = FrScene.create();

        obj.onIdle = FrCanvas.onIdle;

        return obj;
    },

    onIdle: function () {
        this.context.clearRect(0, 0, this.canvas.width, this.canvas.height);
        this.curScene.onRender(this);
    }
};