package com.example.codechemduckgame.service;

import com.example.codechemduckgame.model.Game;
import com.example.codechemduckgame.model.Move;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.stereotype.Service;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

@Service
public class GameService {
    private Game game;

    public Game start(int lvlNum) {
        game = loadGame(lvlNum);
        return game;
    }

    public Game move(Move move) {
        return game.move(move.getDirection()[0], move.getDirection()[1]);
    }

    public Game undo() {
        return game.undo();
    }

    private Game loadGame(int lvlNum) {
        ObjectMapper objectMapper = new ObjectMapper();
        try {
            InputStream inputStream = getClass().getClassLoader().getResourceAsStream("data/level" + lvlNum + ".json");
            if (inputStream == null) {
                throw new FileNotFoundException("File not found: data/level" + lvlNum + ".json");
            }
            return objectMapper.readValue(inputStream, Game.class);

        } catch (IOException e) {
            throw new RuntimeException("Failed to load game level " + lvlNum, e);
        }
    }
}
