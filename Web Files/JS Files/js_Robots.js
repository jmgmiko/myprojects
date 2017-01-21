var name_r1=["Cut Man", "Guts Man", "Ice Man", "Bomb Man", "Fire Man", "Elec Man"];
var weapon_r1=["Rolling Cutter", "Super Arm", "Ice Slasher", "Hyper Bomb", "Fire Storm", "Thunder Beam"];
var num;
var weakness_r1;

$(document).ready(function(){
    $(".box").on("click", function(){
        $(this).css("background-color", "gold");
        $(this).children("h3").css("font-weight", "bolder");
        cleanCard($(this).siblings());
        addHTML(this);
        $(this).children(".name").show();
        $(this).siblings().children(".name").hide();
    });
    $(".box").on("click", ".btn", function(){
        $("#info").children(".look").html("<h1>Name: "+name_r1[num-1]+"<br>Weapon: "+weapon_r1[num-1]+"<br>Weakness: "+weakness_r1+"</h1>");
        $(this).parent().parent().css("border-width", "10px");
    });
});

function cleanCard (obj) {
    $(obj).css("background-color", "white");
    $(obj).css("font-weight", "normal");
    $(obj).css("border-width", "3px");
}

function addHTML (object) {
    num=parseInt($(object).children("h3").text());
    switch (num) {
        case 1:
            weakness_r1="Super Arm";
        break;
        case 2:
            weakness_r1="Hyper Bomb";
        break;
        case 3:
            weakness_r1="Thunder Beam";
        break;
        case 4:
            weakness_r1="Fire Storm";
        break;
        case 5:
            weakness_r1="Ice Slasher";
        break;
        case 6:
            weakness_r1="Rolling Cutter";
        break;
    }
    $(object).children(".name").html(name_r1[num-1]+"<br><button class='btn btn-primary'>SELECT</button>");
}
