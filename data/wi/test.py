import tkinter as tk
from tkinter import filedialog
import os

ROWS = 8
COLS = 5
CELL_SIZE = 50  # pixel size of each cell


class GridApp:
    def __init__(self, root):
        self.root = root
        self.root.title("5x8 Grid Drawing")

        # Internal grid state (0 = empty, 1 = filled)
        self.grid_state = [[0 for _ in range(COLS)] for _ in range(ROWS)]

        # Create canvas
        self.canvas = tk.Canvas(root, width=COLS * CELL_SIZE, height=ROWS * CELL_SIZE, bg="white")
        self.canvas.pack()

        # Draw grid rectangles
        self.rects = [[None for _ in range(COLS)] for _ in range(ROWS)]
        for r in range(ROWS):
            for c in range(COLS):
                x1, y1 = c * CELL_SIZE, r * CELL_SIZE
                x2, y2 = x1 + CELL_SIZE, y1 + CELL_SIZE
                rect = self.canvas.create_rectangle(x1, y1, x2, y2, fill="white", outline="black")
                self.rects[r][c] = rect

        # Mouse event bindings
        self.canvas.bind("<Button-1>", self.start_draw)
        self.canvas.bind("<B1-Motion>", self.draw_drag)
        self.canvas.bind("<ButtonRelease-1>", self.end_draw)

        self.drawing = False
        self.draw_value = 1  # whether we are painting 1s or 0s

        # Buttons
        button_frame = tk.Frame(root)
        button_frame.pack(pady=10)

        save_button = tk.Button(button_frame, text="Save", command=self.save_to_file)
        save_button.grid(row=0, column=0, padx=5)

        reset_button = tk.Button(button_frame, text="Reset", command=self.reset_grid)
        reset_button.grid(row=0, column=1, padx=5)

    def start_draw(self, event):
        """Start drawing on mouse press."""
        self.drawing = True
        row, col = event.y // CELL_SIZE, event.x // CELL_SIZE
        if 0 <= row < ROWS and 0 <= col < COLS:
            # Decide mode: paint 1 if currently 0, paint 0 if currently 1
            self.draw_value = 0 if self.grid_state[row][col] == 1 else 1
            self.apply_draw(row, col)

    def draw_drag(self, event):
        """Draw while dragging."""
        if self.drawing:
            row, col = event.y // CELL_SIZE, event.x // CELL_SIZE
            if 0 <= row < ROWS and 0 <= col < COLS:
                self.apply_draw(row, col)

    def end_draw(self, event):
        """Stop drawing on mouse release."""
        self.drawing = False

    def apply_draw(self, row, col):
        """Apply the drawing action to a cell."""
        self.grid_state[row][col] = self.draw_value
        color = "black" if self.draw_value == 1 else "white"
        self.canvas.itemconfig(self.rects[row][col], fill=color)

    def reset_grid(self):
        """Clear the grid to all zeros (white)."""
        for r in range(ROWS):
            for c in range(COLS):
                self.grid_state[r][c] = 0
                self.canvas.itemconfig(self.rects[r][c], fill="white")

    def save_to_file(self):
        """Save grid state as 8-byte binary file for LCD custom char (5x8 pixels)."""
        default_dir = os.getcwd()
        file_path = filedialog.asksaveasfilename(
            defaultextension=".bin",
            filetypes=[("Binary files", "*.bin"), ("All files", "*.*")],
            initialdir=default_dir
        )
        if not file_path:
            return

        byte_data = bytearray()
        for r in range(ROWS):
            val = 0
            for c in range(COLS):
                val |= (self.grid_state[r][c] & 1) << (4 - c)  # col 0 → bit 4
            byte_data.append(val)

        with open(file_path, "wb") as f:
            f.write(byte_data)

        print(f"Saved to {file_path}")




if __name__ == "__main__":
    root = tk.Tk()
    app = GridApp(root)
    root.mainloop()
