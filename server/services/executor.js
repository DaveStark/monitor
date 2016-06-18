var exec = require('child_process').execFile;

/**
* app name of the executable
* args[] array with whole arguments
* try this in linux and windows as well
**/
var openApp() = function(app, args){
  console.log('Attempting to open an app...');
  exec(app, arg, function(err, data){
    if(err)
      console.log(err);
    else
      console.log('App successfully executed !');

    if(data)
      console.log(data.toString());
  });
}