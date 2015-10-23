function getPixel(imgData, index) {
    var i = index * 4,
        d = imgData.data;
    return [d[i], d[i + 1], d[i + 2], d[i + 3]] // [R,G,B,A]
}
// AND/OR
function getPixelXY(imgData, x, y) {
    return getPixel(imgData, y * imgData.width + x);
}
(function() {
    var flickrAPI = "https://api.flickr.com/services/feeds/photos_public.gne?jsoncallback=?";
    $.getJSON(flickrAPI, {
        tags: "eye,moleskine",
        tagmode: "and",
        format: "json"
    }).done(function(data) {
        // cool we have a json now
        var uniqueclass;
        $.each(data.items, function(i, item) {
            //var imagelink = "<a href='" + item.link + "'><img src='" + item.media.m +"''></a>";

            uniqueclass = "photo" + i;
            // $("<img>").attr("src", item.media.m).appendTo("#wrapper").attr("id", uniqueclass);
            //$(imagelink).appendTo("#wrapper");
            console.log(uniqueclass);
            var imagelink = "<a href='" + item.link + "'><div id='" + uniqueclass + "' class='mypicture " + uniqueclass + "' style='background-image: url('" + item.media.m + " ')'></div></a>";
            $(imagelink).appendTo("#wrapper");
            console.log(item.tags);
            cssuniqueclass = "." + uniqueclass;
            $(cssuniqueclass).css("background-image", "url('" + item.media.m + "')");
            $(cssuniqueclass).css("margin-left", Math.random(1) * 100);
            $(cssuniqueclass).css("margin-top", Math.random(1) * 100);
            // svg
            var svgElement = $('<svg width="400px" height="400px"><circle fill="#ff0000" cx="' + Math.random(1)*50+ '"px cy="200px" r="40px"></circle></svg>');
            $("#"+uniqueclass).append(svgElement);
            /*
            // TRY OUT THIS CANVAS THING
            var img = document.getElementById(uniqueclass); //("img")[0];   // your image goes here
            var canvas = document.createElement('canvas');
            canvas.width = img.width;
            canvas.height = img.height;
            canvas.getContext('2d').drawImage(img, 0, 0, img.width, img.height);
            // img = $('#yourImage')[0];                     // can use jquery for selection
            var pixelData = canvas.getContext('2d').getImageData(0, 0, canvas.width, canvas.height);
            console.log(pixelData);
            // The magic®
            //getPixel(pixelData, 852); // returns array [red, green, blue, alpha]
            //getPixelXY(pixelData, 1, 1); // same pixel using x,y
            console.log("this far");
            console.log(getPixel(pixelData, 852)); // returns array [red, green, blue, alpha]
            */
            if (i == 20) { // break
                return false;
            }
        })
        console.log(data);
    })
})();