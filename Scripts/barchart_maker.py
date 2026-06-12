import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

raw = pd.read_csv('../Data/combined_output.csv')
raw.replace("Aluminum Wall 6mm (BaseLine)", "Aluminum", inplace=True)
raw.replace("Composite (27H:13S)", "HELIOS", inplace=True)
materials_raw = raw[["Material", " Dose (rad)", " High Risk Events"]]
materials = materials_raw["Material"].unique()

materials_rad_dict = {mat: 0 for mat in materials}
materials_HRE_dict = {mat: 0 for mat in materials}

for i in range(len(materials_raw)):
    row = materials_raw.iloc[i]
    materials_rad_dict[row["Material"]] += row[" Dose (rad)"]
    materials_HRE_dict[row["Material"]] += row[" High Risk Events"]

GREY      = "#666666"
DARK_GREY = "#333333"
COLORS    = ["#130059", "#a50000", "#00de22"]

plt.rcParams.update({
    "font.family":     "TeX Gyre Schola",
    "text.color":      DARK_GREY,
    "axes.labelcolor": GREY,
    "xtick.color":     GREY,
    "ytick.color":     GREY,
    "axes.edgecolor":  GREY,
})

def plot_bars(labels, values, colors, ylabel, title, unit_scale=1.0, filename="plot.png"):
    values_scaled = [v * unit_scale for v in values]
    x = np.arange(len(labels))
    bar_width = 0.5
    max_val = max(values_scaled)

    fig, ax = plt.subplots(figsize=(5, 6))

    for i, (val, color) in enumerate(zip(values_scaled, colors)):
        ax.bar(x[i] + 0.02, val - val * 0.01, width=bar_width, color="#333333", zorder=1)
        ax.bar(x[i], val, width=bar_width, color=color, zorder=2)
        ax.text(
            x[i], val + max_val * 0.02,
            f"{val:,.1f}",
            ha="center", va="bottom",
            fontsize=9, color=DARK_GREY,
            zorder=3,
        )

    ax.set_xlim(-0.5, len(labels) - 0.5)
    ax.set_ylim(0, max_val * 1.15)
    ax.set_xticks(x)
    ax.set_xticklabels(labels, fontsize=10)
    ax.set_ylabel(ylabel, fontsize=10, labelpad=8)
    ax.set_title(title, fontsize=13, fontweight="bold", color=DARK_GREY, pad=12)

    ax.yaxis.grid(True, linestyle="dashed", linewidth=0.5, color="#cccccc")
    ax.set_axisbelow(True)
    ax.spines["top"].set_visible(False)
    ax.spines["right"].set_visible(False)
    ax.spines["left"].set_visible(False)

    plt.tight_layout()
    if ylabel == "Dose (Arad)":
        plt.savefig("BarAggregate_Radiation", dpi=300, bbox_inches="tight")  # Save BEFORE show
    else:
        plt.savefig("BarAggregate_HRE", dpi=300, bbox_inches="tight")
    plt.show()


plot_bars(
    labels=list(materials_rad_dict.keys()),
    values=list(materials_rad_dict.values()),
    colors=COLORS,
    ylabel="Dose (Arad)",
    title="Total Radiation Dose by Material",
    unit_scale=1e18,
    filename="total_dose.png",
)

plot_bars(
    labels=list(materials_HRE_dict.keys()),
    values=list(materials_HRE_dict.values()),
    colors=COLORS,
    ylabel="High Risk Events (Thousands)",
    title="Total High Risk Events by Material",
    unit_scale=1/1e3,
    filename="total_HRE.png",
)
