cordova.define("cordova-plugin-opcvExample.opcvExample", function(require, exports, module) {
               var exec = require('cordova/exec');
               
               function OpcvExample() {
               console.log("opcvExample.js: is created");
               }
               
               OpcvExample.prototype.startScan = function(callback){
               console.log("opcvExample.js: startScan");
               
               exec(function(result){
                        callback(result);
                    },
                    function(result){
                    /*alert("Error" + reply);*/
                    },"opcvExample","startScan",[]);
               }
               
               var opcvExample = new OpcvExample();
               module.exports = opcvExample;

});
