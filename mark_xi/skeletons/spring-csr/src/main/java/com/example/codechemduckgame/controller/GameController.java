package com.example.codechemduckgame.controller;

import com.example.codechemduckgame.model.Game;
import com.example.codechemduckgame.model.Move;
import com.example.codechemduckgame.service.GameService;
import org.springframework.web.bind.annotation.*;

@RestController
@CrossOrigin
@RequestMapping("/api/game")
public class GameController {

    final GameService gameService;

    public GameController(GameService gameService) {
        this.gameService = gameService;
    }

    @GetMapping("/start/{lvlNum}")
    public Game start(@PathVariable String lvlNum) {
        return gameService.start(Integer.parseInt(lvlNum));
    }

    @PostMapping("/move")
    public Game move(@RequestBody Move move) {
        return gameService.move(move);
    }

    @GetMapping("/undo")
    public Game undo() {
        return gameService.undo();
    }
}
