//= require phaser

var game = new Phaser.Game(800, 600, Phaser.AUTO, 'phaser-example',
    { preload: preload, create: create });

function preload() {
    game.load.image('einstein', 'assets/example.png');
}

function create() {
    var image = game.add.sprite(20, 20, 'einstein');
}