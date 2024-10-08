package com.example.codechemduckgame.model;

import com.fasterxml.jackson.annotation.JsonIgnore;
import lombok.Getter;
import lombok.Setter;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;
import java.util.Stack;

@Setter
@Getter
public class Game {
    private int id;
    private int[] player;
    private String[][] board;
    private String state;
    @JsonIgnore
    private Stack<String[][]> boardHistory = new Stack<>();
    @JsonIgnore
    private Stack<int[]> playerHistory = new Stack<>();

    public Game(int id, int[] player, String[][] board, String state) {
        this.id = id;
        this.player = player;
        this.board = board;
        this.state = state;
    }

    public Game() {
    }

    @Override
    public String toString() {
        return "Game{" +
                "id=" + id +
                ", player=" + Arrays.toString(player) +
                ", board=" + Arrays.toString(board) +
                ", state='" + state + '\'' +
                '}';
    }

    public Game move(int x, int y) {

        String[][] copy = new String[board.length][];
        for (int i = 0; i < board.length; i++) {
            copy[i] = board[i].clone();
        }

        boardHistory.push(copy);
        playerHistory.push(this.player.clone());

        makeStone();
        if (isWall(player[0], player[1])) {
            state = "lost";
            return this;
        }


        player[0] = player[0] + x;
        player[1] = player[1] + y;

        if (isWall(player[0], player[1])) {
            player = playerHistory.pop();
            board = boardHistory.pop();
            return this;
        }

        if (isBox(player[0], player[1])) {
            if (board[player[0] + x][player[1] + y].equals("B") || board[player[0] + x][player[1] + y].equals("#")
                    || board[player[0] + x][player[1] + y].equals("G")) {
                player = playerHistory.pop();
                board = boardHistory.pop();
                return this;
            }
            board[player[0]][player[1]] = ".";
            board[player[0] + x][player[1] + y] = "B";
        }

        spread();
        checkStone();

        if (isLava(player[0], player[1])) {
            state = "lost";
            return this;
        }

        if (isWon(player[0], player[1])) {
            state = "won";
            return this;
        }
        return this;
    }

    public Game undo() {
        if (boardHistory.empty() || playerHistory.empty()) {
            return this;
        }

        this.board = boardHistory.pop();
        this.player = playerHistory.pop();

        return this;
    }

    private boolean isWall(int x, int y) {
        return board[x][y].equals("#");
    }

    private boolean isBox(int x, int y) {
        return board[x][y].equals("B");
    }

    private boolean isWon(int x, int y) {
        return board[x][y].equals("G");
    }

    private boolean isLava(int x, int y) {
        return board[x][y].equals("L");
    }

    private void spread() {
        Set<String> history = new HashSet<>();
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                if ((board[i][j].equals("L") || board[i][j].equals("W")) && history.add(i + " " + j)) {

                    if (i < board[i].length - 1 && board[i + 1][j].equals(".")) {
                        board[i + 1][j] = board[i][j];
                        history.add((i + 1) + " " + j);
                    }

                    if (i > 0 && board[i - 1][j].equals(".")) {
                        board[i - 1][j] = board[i][j];
                        history.add((i - 1) + " " + j);
                    }

                    if (j < board[i].length - 1 && board[i][j + 1].equals(".")) {
                        board[i][j + 1] = board[i][j];
                        history.add(i + " " + (j + 1));
                    }
                    if (j > 0 && board[i][j - 1].equals(".")) {
                        board[i][j - 1] = board[i][j];
                        history.add(i + " " + (j - 1));
                    }
                }
            }
        }
    }

    private void checkStone() {
        for (int i = 1; i < board.length - 1; i++) {
            for (int j = 1; j < board[i].length - 1; j++) {
                if (board[i][j].equals(".")) {
                    if (board[i + 1][j].equals("W") || board[i][j + 1].equals("W")) {
                        if (board[i - 1][j].equals("L")) {
                            board[i][j] = "C";
                        }

                        if (board[i][j - 1].equals("L")) {
                            board[i][j] = "C";
                        }
                    }
                    if (board[i + 1][j].equals("L") || board[i][j + 1].equals("L")) {
                        if (board[i - 1][j].equals("W")) {
                            board[i][j] = "C";
                        }

                        if (board[i][j - 1].equals("W")) {
                            board[i][j] = "C";
                        }
                    }


                }
            }
        }
    }

    private void makeStone() {
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                if (board[i][j].equals("C")) {
                    board[i][j] = "#";
                }
                if (board[i][j].equals("L")) {
                    if (board[i + 1][j].equals("W")) {
                        board[i][j] = "#";
                    }
                    if (board[i - 1][j].equals("W")) {
                        board[i][j] = "#";
                    }
                    if (board[i][j + 1].equals("W")) {
                        board[i][j] = "#";
                    }
                    if (board[i][j - 1].equals("W")) {
                        board[i][j] = "#";
                    }

                }
            }
        }
    }
}
