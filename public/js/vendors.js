"use strict";
var buttons = document.getElementById('vendorPeople').getElementsByTagName('a'),
    len = buttons.length,
    i   = 0;

for (i=0; i<len; i++) {
    buttons[i].addEventListener('click', function (e) {
        e.preventDefault();
        var input  = document.getElementById('people'),
            re     = /person_id=(\d+)/,
            result = re.exec(e.target.getAttribute('href')),
            vendor = result[1],
            ids    = input.value.split(','),
            out    = ids.filter(function (el) { return Number(el) != Number(vendor); });

        input.value = out.join(',');
        e.target.parentNode.remove();

        return false;
    }, false);
}
