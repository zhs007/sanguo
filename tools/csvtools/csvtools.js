/**
 * Created by zhs007 on 15/5/16.
 */

var xlsx2csv = require('xlsx2csv');

var xlsxroot = '../../res/static/';
var csvroot = '../../sanguo/Resources/res/csv/';

var files = ['actioninfo', 'soldierinfo'];

for (var i = 0; i < files.length; ++i) {
    xlsx2csv.xlsx2csv(xlsxroot + files[i] + '.xlsx', csvroot + files[i] + '.csv');

    console.log(xlsxroot + files[i] + '.xlsx => ' + csvroot + files[i] + '.csv');
}