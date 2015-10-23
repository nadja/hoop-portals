var persistent = 0;

function play() {
    console.log('ok');
    var cuser_input = document.getElementById("user-input"); // get a particular input
    var user_move = cuser_input.value.toLowerCase();
    var possible_moves = ["rock", "paper", "scissors", "rock"];
    var imagesarr = ["rock.gif", "paper.gif", "scissors.gif", "rock.gif"];
    var i = Math.floor(Math.random() * 3);
    var computer_move = possible_moves[i];
    console.log("computer_move", computer_move);
    // setup velocity
    $("#paper").velocity({
        fill: "#000"
    });
    $("#rock").velocity({
        fill: "#000"
    });
    $("#scissors").velocity({
        fill: "#000"
    });
    // end veloctiy
    var outcome; // who won?
    outcome = "player wins"; // default
    if (computer_move === user_move) {
        outcome = 'draw';
        persistent++;
        console.log(persistent);
    }
    if (user_move === (possible_moves[i + 1])) { // 1-up
        outcome = "computer wins";
    }
    // end outcome
    var computer_div = document.getElementById("computer-move");
    computer_div.innerHTML = "computer chose: " + computer_move + "<br><img src='" + imagesarr[i] + "' width='100'>";
    var outcomediv = document.getElementById("outcome");
    // draw outcome 
    if (outcome === "computer wins") {
        $("#scissors").velocity({
            fill: "#F00"}).velocity({translateY: -100});
        
        outcomediv.innerHTML = "outcome = " + outcome + "<br><img src='images.jpeg'>";
    } else if (outcome === "player wins") {
        $("#rock").velocity({
            fill: "#F00"
        });
        outcomediv.innerHTML = "outcome = " + outcome + "<br><img src='magicman.jpg'>";
    } else {
        $("#paper").velocity({
            fill: "#F00"
        });
        outcomediv.innerHTML = "outcome: " + outcome + "<br><img src='draw.jpg'>";;
    }
} // end play function