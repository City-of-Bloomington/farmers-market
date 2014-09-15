"use strict";

var URL = {
    replaceParam: function (href, key, value) {
        var regex;

        regex = new RegExp("(" + key + "=)\.\*?(;|$)");
        if (regex.test(href)) {
            href = href.replace(regex, '$1' + value + '$2');
        }
        else {
            if(href.indexOf('?') === -1) {
                href += '?' + key + '=' + value;
            }
            else {
                href += ';' + key + '=' + value;
            }
        }

        return href;
    }
};
