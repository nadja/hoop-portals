function recurve(tags, num) {
    var flickrAPI = "https://api.flickr.com/services/feeds/photos_public.gne?jsoncallback=?";
    num--;
    if (num == 0) {
        return false;
    }
    $.getJSON(flickrAPI, {
        tags: tags,
        tagmode: "and",
        format: "json"
    }).done(function(data) {
        // cool we have a json now
        $.each(data.items, function(i, item) {
            var uniqueclass;
            uniqueclass = "photo" + num;
            var imagelink = "<a href='" + item.link + "'><div id='" + uniqueclass + "' class='mypicture " + uniqueclass + "' style='background-image: url('" + item.media.m + " ')'>" + item.tags.split(' ')[Math.floor(Math.random(3) * 3)] + "</div></a>";
            $(imagelink).appendTo("#wrapper");
            console.log(item.tags);
            cssuniqueclass = "." + uniqueclass;
            $(cssuniqueclass).css("background-image", "url('" + item.media.m + "')");
            $(cssuniqueclass).css("margin-left", Math.random(1) * 100);
            $(cssuniqueclass).css("margin-top", Math.random(1) * 100);
            console.log(item.tags.split(' ')[Math.floor(Math.random(3) * 3)]);
            console.log(num);
            $(item.tags.split(' ')[Math.floor(Math.random(3) * 3)]).appendTo("#" + uniqueclass);
            recurve(item.tags.split(' ')[Math.floor(Math.random(3) * 3)]+", cat", num);
            if (i == 0) { // break
                return false;
            }
        })
    })
}
recurve("necca, lyra", 20);