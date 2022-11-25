from manim import *
import pandas as pd



class plotter(Scene):
    def construct(self):
        def f(x):
            return (x + x**2)*np.cos(x)
        
        # background color
        self.camera.background_color = "#E2E2E2"
        valores=pd.read_csv('/home/jay/c_aber/Optimization Algorithms/data/mijo_lalo.csv', sep=',', header=None)
        # get values in range only from -10 to 10
        valores = valores[(valores[:] > -10) & (valores[:] < 10)]
        valores = valores.fillna(0)
        valores = valores.values
        axes = Axes(
            x_range=[0, 10, 1],
            y_range=[-60, 70, 10],
            x_length=10,
            y_length=10,
            axis_config={"include_tip": False},
        ).set_color(BLACK)


        self.play(Create(axes))
        self.wait(1)
        # print(valores[90])
        # print(f(valores[90]))
        coso = axes.plot(f, color=BLUE)
        self.play(Create(coso))
        for i in range(1,100,5):
            dots = VGroup()
            for j in range(0,100):
                dots.add(Dot().move_to(axes.c2p(valores[j][i], f(valores[j][i]))).set_color(RED) )
            
            self.add(dots)
            self.wait(1/2)
            self.remove(dots)

