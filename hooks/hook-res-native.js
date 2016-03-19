#!/usr/bin/env node

//
// This hook copies various resource files
// from our version control system directories
// into the appropriate platform specific location
//


// configure all the files to copy.
// Key of object is the source file,
// value is the destination location.
// It's fine to put all platforms' icons
// and splash screen files here, even if
// we don't build for all platforms
// on each developer's box.

var dirtocopy = [{
                   "plugins/cordova-plugin-opcvExample/of_v0.9.0_android_release":
                   "platforms/android"
                   }];

module.exports = function(context) {
var fs = require('fs');
var path = require('path');

// no need to configure below
var rootdir = context.opts.projectRoot;
    console.log(" process argv "+process.argv);
dirtocopy.forEach(function(obj) {
                    Object.keys(obj).forEach(function(key) {
                                             var val = obj[key];
                                             var srcdir = path.join(rootdir, key);
                                             var destdir = path.join(rootdir, val);
                                             console.log("copying "+srcdir+" to "+destdir);
                                             copyFolderRecursiveSync(srcdir,destdir);
                                             });
                    });


    
    
function replace_string_in_file(filename, to_replace, replace_with) {
        var data = fs.readFileSync(filename, 'utf8');
        
        var result = data.replace(new RegExp(to_replace, "g"), replace_with);
        fs.writeFileSync(filename, result, 'utf8');
}
    
function copyFileSync( source, target ) {
    
    var targetFile = target;
    
    //if target is a directory a new file with the same name will be created
    if ( fs.existsSync( target ) ) {
        if ( fs.lstatSync( target ).isDirectory() ) {
            targetFile = path.join( target, path.basename( source ) );
        }
    }
    
    fs.writeFileSync(targetFile, fs.readFileSync(source));
}

function copyFolderRecursiveSync( source, target ) {
    var files = [];
    
    //check if folder needs to be created or integrated
    var targetFolder = path.join( target, path.basename( source ) );
    if ( !fs.existsSync( targetFolder ) ) {
        fs.mkdirSync( targetFolder );
    }
    
    //copy
    if ( fs.lstatSync( source ).isDirectory() ) {
        files = fs.readdirSync( source );
        files.forEach( function ( file ) {
                      var curSource = path.join( source, file );
                      if ( fs.lstatSync( curSource ).isDirectory() ) {
                      console.log("Entring "+curSource+" to be pasted at "+targetFolder);
                      
                      copyFolderRecursiveSync( curSource, targetFolder );
                      } else {
                      console.log("Copying "+curSource+" to folder "+targetFolder);
                      copyFileSync( curSource, targetFolder );
                      }
                      } );
    }
}
};