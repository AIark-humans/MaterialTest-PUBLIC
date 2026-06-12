import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
import glob
import os

fm._load_fontmanager(try_read_cache=False)

GREY = "#666666"
DARK_GREY = "#333333"

plt.rcParams.update({
    "font.family":        "TeX Gyre Schola",
    "text.color":         DARK_GREY,
    "axes.labelcolor":    GREY,
    "xtick.color":        GREY,
    "ytick.color":        GREY,
    "axes.edgecolor":     GREY,
})

csv_files = glob.glob("../Data/*.csv")
csv_files.remove("combined_output.csv")

COLORS = ["#130059", "#00de22", "#a50000"]

for f in csv_files:
    raw = pd.read_csv(f)
    raw = raw.sort_values(by=["Material", " Thickness (cm)"]).reset_index(drop=True)
    raw = raw[raw[" Thickness (cm)"] <= 15]  # Cap at 15 here, before anything else

    materials = raw["Material"].unique()
    num = "".join(char for char in f if char.isdigit())

    materials_rad_dict = {mat: [] for mat in materials}
    materials_HRE_dict = {mat: [] for mat in materials}

    for i in range(len(raw)):
        row = raw.iloc[i]
        materials_rad_dict[row["Material"]].append(row[" Dose (rad)"] * 1e18)
        materials_HRE_dict[row["Material"]].append(row[" High Risk Events"] / 1e3)

    thicknesses = sorted(raw[" Thickness (cm)"].unique())

    fig, ax = plt.subplots(figsize=(6, 5))

    for mat, color in zip(materials, COLORS):
        mat_name = mat
        if mat == "Composite (27H:13S)":
            mat_name = "HELIOS"

        if mat == "Aluminum Wall 6mm (BaseLine)":
            mat_name = "Aluminum"

        ax.plot(
            thicknesses,
            materials_rad_dict[mat],
            color=color,
            marker="o",
            ms=5,
            markerfacecolor=color,
            markeredgecolor=color,
            linewidth=1.5,
            linestyle="dashed",
            label= mat_name,
        )

    ax.set_title(
        f"Radiation Dose vs. Material Thickness at {num} MeV",
        fontsize=13,
        fontweight="bold",
        color=DARK_GREY,
        pad=12,
    )
    ax.set_xlabel("Thickness (cm)", fontsize=10, labelpad=8)
    ax.set_ylabel("Dose (Arads)", fontsize=10, labelpad=8)

    ax.yaxis.grid(True, linestyle="dashed", linewidth=0.5, color="#cccccc")
    ax.set_axisbelow(True)

    ax.spines["top"].set_visible(False)
    ax.spines["right"].set_visible(False)
    ax.spines["left"].set_visible(False)

    ax.set_xticks([2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15])

    ax.legend(
        frameon=False,
        fontsize=9,
        labelcolor=DARK_GREY,
    )

    plt.tight_layout()
    plt.savefig(f"plot_Rad_{num}MeV.png", dpi=300, bbox_inches="tight")
    plt.show()











