cordova.define("cordova-plugin-opcvExample.opcvExample", function(require, exports, module) {
               var exec = require('cordova/exec');
               
               function OpcvExample() {
               console.log("opcvExample.js: is created");
               }
               
               OpcvExample.prototype.showToast = function(aString){
               console.log("opcvExample.js: showToast");
               
               exec(function(result){
                    alert("OK" + reply);
                    },
                    function(result){
                    alert("Error" + reply);
                    },"opcvExample",aString,[]);
               }
               
               var opcvExample = new OpcvExample();
               module.exports = opcvExample;

});
