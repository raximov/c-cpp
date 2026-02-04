class Point {
  constructor(x, y) {
    this.x = x;
    this.y = y;
  }
}

document.addEventListener("DOMContentLoaded", () => {
  backend_module().then((Module) => {
    let mazePointer = Module.ccall("create_maze", "number", null, null);
    const max_size_value = Module.ccall("get_max_size", "number", null, null);
    const load_maze_from_content = Module.cwrap(
      "load_maze_from_content",
      null,
      ["number", "number"],
    );
    let path_pointer = Module.ccall("create_path", "number", null, null);
    const get_solution_bfs = Module.cwrap("get_solution_bfs", "number", [
      "number",
      "number",
      "number",
      "number",
    ]);
    const areStartEndValid = Module.cwrap("areStartEndValid", "number", [
      "number",
      "number",
      "number",
    ]);
    const generate_maze = Module.cwrap("generate_maze", null, [
      "number",
      "number",
      "number",
    ]);
    const startPtr = Module._malloc(8);
    const endPtr = Module._malloc(8);
    const form = document.querySelector("#form1");
    const form2 = document.querySelector("#form2");
    const canvas = document.querySelector("canvas");
    const ctx = canvas.getContext("2d");
    let is_loaded = false;
    let is_path = false;
    let start = new Point(0, 0);
    let end = new Point(0, 0);
    write_point(startPtr, start);
    write_point(endPtr, end);
    resizeCanvas();

    let path = [];
    let maze = {
      rows: 0,
      cols: 0,
      vertical_walls: [],
      horizontal_walls: [],
    };

    form.file.addEventListener("change", (e) => {
      const file = e.target.files[0];
      const reader = new FileReader();
      reader.onload = (e) => {
        let content = e.target.result;
        let contentPtr = Module._malloc(content.length + 1);
        Module.stringToUTF8(content, contentPtr, content.length + 1);
        load_maze_from_content(contentPtr, mazePointer);
        read_maze();
        Module._free(contentPtr);
        zeros();
        call_render();
      };
      reader.readAsText(file);
    });

    form.path.addEventListener("change", (e) => {
      const result = areStartEndValid(mazePointer, startPtr, endPtr);
      if (is_loaded && result === 0) {
        is_path = e.target.checked;
        call_render();
      } else {
        e.target.checked = false;
      }
    });

    form.startX.addEventListener("change", (e) => {
      start.x = e.target.value;
      write_point(startPtr, start);
      call_render();
    });

    form.startY.addEventListener("change", (e) => {
      start.y = e.target.value;
      write_point(startPtr, start);
      call_render();
    });

    form.endX.addEventListener("change", (e) => {
      end.x = e.target.value;
      write_point(endPtr, end);
      call_render();
    });

    form.endY.addEventListener("change", (e) => {
      end.y = e.target.value;
      write_point(endPtr, end);
      call_render();
    });

    window.addEventListener("resize", () => {
      resizeCanvas();
    });

    form2.addEventListener("submit", (e) => {
      e.preventDefault();
      e.stopPropagation();
      generate_maze(
        mazePointer,
        parseInt(form2.rows.value),
        parseInt(form2.cols.value),
      );
      read_maze();
      zeros();
      call_render();
    });

    document.querySelector(".download").addEventListener("click", (e) => {
      if (is_loaded) {
        if (e.target.href) {
          URL.revokeObjectURL(e.target.href);
        }
        let content = `${maze.rows} ${maze.cols}\n`;
        for (let i = 0; i < maze.rows; ++i) {
          for (let j = 0; j < maze.cols; ++j) {
            content += `${maze.vertical_walls[i][j]} `;
          }
          content += `\n`;
        }
        content += `\n`;
        for (let i = 0; i < maze.rows; ++i) {
          for (let j = 0; j < maze.cols; ++j) {
            content += `${maze.horizontal_walls[i][j]} `;
          }
          content += `\n`;
        }
        const blob = new Blob([content], { type: "text/plain" });
        const url = window.URL.createObjectURL(blob);
        e.target.href = url;
        e.target.download = "maze.txt";
      }
    });

    function read_maze() {
      maze.rows = Module.getValue(mazePointer, "i32");
      maze.cols = Module.getValue(mazePointer + 4, "i32");
      let offset = 8;
      for (let i = 0; i < maze.rows; i++) {
        maze.vertical_walls[i] = [];
        for (let j = 0; j < maze.cols; j++) {
          maze.vertical_walls[i][j] = Module.getValue(
            mazePointer + offset + (i * max_size_value + j) * 4,
            "i32",
          );
        }
      }
      offset += max_size_value * max_size_value * 4;
      for (let i = 0; i < maze.rows; i++) {
        maze.horizontal_walls[i] = [];
        for (let j = 0; j < maze.cols; j++) {
          maze.horizontal_walls[i][j] = Module.getValue(
            mazePointer + offset + (i * max_size_value + j) * 4,
            "i32",
          );
        }
      }
    }

    function read_path() {
      for (let i = 0; i < max_size_value; i++) {
        path[i] = [];
        let row_pointer = Module.getValue(path_pointer + i * 4, "*");
        for (let j = 0; j < max_size_value; j++) {
          path[i][j] = Module.getValue(row_pointer + j * 4, "i32");
        }
      }
    }

    function call_render() {
      if (is_loaded) {
        if (is_path) {
          get_solution_bfs(mazePointer, startPtr, endPtr, path_pointer);
          read_path();
        }
        draw_maze();
      }
    }

    function draw_maze() {
      let square_size = 6;
      if (maze.cols > 20 || maze.rows > 20) {
        square_size = 1;
      }
      let square_width = square_size / 2;
      let drawingWidth = canvas.width - square_size;
      let drawingHeight = canvas.height - square_size;
      let cell_height = drawingHeight / maze.rows;
      let cell_width = drawingWidth / maze.cols;
      let x, y;
      ctx.clearRect(0, 0, canvas.width, canvas.height);
      for (let i = 0; i < maze.rows; ++i) {
        for (let j = 0; j < maze.cols; ++j) {
          y = square_width + i * cell_height;
          x = square_width + j * cell_width;
          draw_path(i, j, cell_width, cell_height, x, y);
          ctx.lineWidth = 1;
          ctx.strokeStyle = "#c2c7d0";
          ctx.fillStyle = "#c2c7d0";
          ctx.fillRect(
            x - square_width,
            y - square_width,
            square_size,
            square_size,
          );
          if (i > 0 && maze.horizontal_walls[i - 1][j] == 1) {
            ctx.beginPath();
            ctx.moveTo(x, y);
            ctx.lineTo(x + cell_width, y);
            ctx.stroke();
          }
          if (j != maze.cols - 1 && maze.vertical_walls[i][j] == 1) {
            ctx.beginPath();
            ctx.moveTo(x + cell_width, y);
            ctx.lineTo(x + cell_width, y + cell_height);
            ctx.stroke();
          }
          if (i == maze.rows - 1) {
            ctx.fillRect(
              x - square_width,
              y + cell_height - square_width,
              square_size,
              square_size,
            );
            ctx.fillRect(
              x + cell_width - square_width,
              y + cell_height - square_width,
              square_size,
              square_size,
            );
          }
          if (j == maze.cols - 1) {
            ctx.fillRect(
              x + cell_width - square_width,
              y - square_width,
              square_size,
              square_size,
            );
            ctx.fillRect(
              x + cell_width - square_width,
              y + cell_height - square_width,
              square_size,
              square_size,
            );
          }
        }
      }
    }

    function draw_path(i, j, cell_width, cell_height, x, y) {
      if (is_path && path[i][j]) {
        ctx.strokeStyle = "red";
        ctx.beginPath();
        if (i > 0 && path[i - 1][j] && !maze.horizontal_walls[i - 1][j]) {
          ctx.moveTo(x + cell_width / 2, y + cell_height / 2);
          ctx.lineTo(x + cell_width / 2, y - cell_height / 2);
        }
        if (j > 0 && path[i][j - 1] && !maze.vertical_walls[i][j - 1]) {
          ctx.moveTo(x + cell_width / 2, y + cell_height / 2);
          ctx.lineTo(x - cell_width / 2, y + cell_height / 2);
        }
        ctx.stroke();
      }
    }

    function read_point(point_pointer, point) {
      point.x = Module.getValue(point_pointer, "i32");
      point.y = Module.getValue(point_pointer + 4, "i32");
    }

    function write_point(point_pointer, point) {
      Module.setValue(point_pointer, point.x, "i32");
      Module.setValue(point_pointer + 4, point.y, "i32");
    }

    function resizeCanvas() {
      canvas.width = canvas.clientWidth;
      canvas.height = canvas.clientHeight;
      call_render();
    }

    function zeros() {
      is_loaded = true;
      form.startX.value = 0;
      form.startY.value = 0;
      form.endX.value = 0;
      form.endY.value = 0;
      start = new Point(0, 0);
      end = new Point(0, 0);
      write_point(startPtr, start);
      write_point(endPtr, end);
      is_path = false;
      form.path.checked = false;
    }
  });
});
