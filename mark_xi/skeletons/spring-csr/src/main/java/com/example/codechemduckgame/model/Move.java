package com.example.codechemduckgame.model;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class Move {
    private int [] direction;
    public Move(int[] direction) {
        this.direction = direction;
    }

    public Move() {
    }
}
