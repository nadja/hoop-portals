var persistent = 0;
document.onkeydown = myscript;
var x1 = 100;
var y1 = 100;

function myscript(e) {
    var movethismuch = 50;
    var charCode = (typeof e.which == "number") ? e.which : e.keyCode
    switch (charCode) {
        case 37: // up
            x1 += movethismuch;
            break;
        case 38: // left
            y1 -= movethismuch;
            break;
        case 40: // down
            y1 += movethismuch;
            console.log(y1);
            break;
        case 39: // dright
            x1 -= movethismuch;
            console.log(x1);
            break;
    } // end switch
    document.getElementById('lion').style.top = y1;
    document.getElementById('lion').style.left = x1;
    console.log(charCode);
}
// end play function}