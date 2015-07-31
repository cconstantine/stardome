function getBrightness() {
    $.ajax({
        method: "get",
        url: "/brightness",
        complete: function(result) {
          console.log(result.responseText);
          $('#ex1').slider('setValue', Number(result.responseText));
        }
    });
}

function setBrightness(values) {
    console.log(values.newValue);
    $.ajax({
        method: "POST",
        url: "/brightness",
        data: values.newValue.toString(),
    });
}

$(function() {
    $('#ex1').slider();
    $('#ex1').slider("on", "change", $.throttle( 100, setBrightness ));

    getBrightness();
    setInterval(getBrightness, 1000);
});
