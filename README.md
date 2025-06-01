# CNN Accelerator (Vitis HLS)

This repository implements a hardware-accelerated CNN block using **Xilinx Vitis HLS 2024.2**. The accelerator consists of:
- A 2D convolution layer with ReLU activation
- A 2×2 max pooling layer
- Designed for Artix-7 FPGAs

<br>

## 📂 Project Structure

cnn-accelerator-vitis-hls/
├── src/ # HLS source files (cnn_block.cpp, etc.)
├── testbench/ # C++ testbench for functional simulation
├── reports/ # Synthesis reports and screenshots
├── docs/ # Performance summary visuals (PNG, etc.)
├── README.md
├── LICENSE
└── .gitignore
<br>

## 🚀 Getting Started

### Requirements
- Vitis HLS 2024.2
- Vivado (optional for IP integration)

### To Simulate:
1. Open Vitis HLS GUI.
2. Create a new project and import `cnn_block.cpp` as top function.
3. Add testbench from `testbench/testbench.cpp`.
4. Run **C Simulation**.

### To Synthesize:
1. Set part: `xa7a12t-cpg238-2I`
2. Click **Run C Synthesis**.
3. View performance and utilization reports.

<br>

## 📊 Performance Summary

### Timing Estimate
| Metric       | Value     |
|--------------|-----------|
| Target Clock | 10.00 ns  |
| Achieved     | 8.178 ns  |
| Uncertainty  | 2.70 ns   |

### Latency
| Metric               | Value      |
|----------------------|------------|
| Latency (cycles)     | 95         |
| Latency (time)       | 0.950 μs   |
| Initiation Interval  | 32         |
| Pipelined            | Yes        |

### HW Interface (AP_MEMORY)
| Port              | Direction | Bitwidth |
|-------------------|-----------|----------|
| input_r_address0  | out       | 6        |
| input_r_address1  | out       | 6        |
| input_r_q0        | in        | 32       |

---

## 🧮 Resource Utilization

| Resource   | Used  | Available | Utilization |
|------------|-------|-----------|-------------|
| BRAM_18K   | 0     | 40        | 0%          |
| DSP        | 55    | 40        | 137% ⚠️     |
| FF         | 17,943| 16,000    | 112% ⚠️     |
| LUT        | 15,518| 8,000     | 193% ⚠️     |
| URAM       | 0     | 0         | 0%          |

⚠️ Resource usage exceeds the available on-chip resources for the selected part (`xa7a12t-cpg238-2I`), and may require:
- Optimization
- Lower parallelism
- Use of a larger FPGA

---

## 📐 Design Compilation Insights

### Instruction Breakdown by Phase

| Phase             | Total Instructions |
|------------------|--------------------|
| Compile/Link     | 136                |
| Unroll/Inline    | 2,640 (total)      |
| Array/Struct     | ~4,688 (across 5 steps) |
| Performance Tuning | ~3,736           |
| HW Transformations | ~2,070           |

> 🔬 The `cnn_block` function is fully unrolled, pipelined, and optimized for parallelism—resulting in higher resource usage but low latency.

---

## 🖼️ Performance Visual

![Timing & Utilization Summary](docs/summary.png)

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

## ✍️ Author

**Siddharth A G**  
Aspiring hardware-software co-design engineer focused on FPGA-based AI accelerators and embedded compute systems.
