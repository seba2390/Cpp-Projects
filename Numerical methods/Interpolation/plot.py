import matplotlib.pyplot as plt
import numpy as np
plt.rc("font", family=["Helvetica", "Arial"])
plt.rc("text", usetex=True)
plt.rc("xtick", top=True, direction="in",labelsize=20)
plt.rc("ytick", right=True, direction="in",labelsize=20)




def load_spline(filename):

    spline_x = np.loadtxt(filename)[:,0]
    spline_y = np.loadtxt(filename)[:,1]

    return spline_x,spline_y


def plot_spline(save_plot=True):

    tab_x, tab_y = np.loadtxt("tabulated_data.txt")[:,0], np.loadtxt("tabulated_data.txt")[:,1]

    lin_spline_x,lin_spline_y = np.loadtxt("lin_spline_data.txt")[:,0], np.loadtxt("lin_spline_data.txt")[:,1] 


    fig, ax = plt.subplots(1,1,figsize=(12,6.5))

    ax.set_xlabel("x",fontsize=22),ax.set_ylabel("y",fontsize=22)

    ax.scatter(tab_x, tab_y, s = 25, c = 'red' ,edgecolors='black',label = "Tabulated points")
    ax.plot(lin_spline_x, lin_spline_y, ls = "-", label = "Linear spline")

    ax.legend()

    if save_plot:
        plt.savefig("plot.jpg",dpi=250)


if __name__ == '__main__':

    plot_spline()
