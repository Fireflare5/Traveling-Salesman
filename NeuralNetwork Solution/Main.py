import numpy as np
import multiprocessing

np.random.seed(0)

class NeuralNetwork:
    def __init__(self, n_inputs, n_neurons, n_outputs, n_layers):
        self.nLayers = n_layers + 1
        self.tanh = Tanh()
        self.weights = [0.01 * np.random.randn(n_inputs,n_neurons)] + [0.01 * np.random.randn(n_neurons, n_neurons)] * n_layers + [0.01 * np.random.randn(n_neurons, n_outputs)]
        self.biases = [np.zeros(shape=(1,n_neurons))] * self.nLayers + [np.zeros(shape=(1,n_outputs))]
        self.inputs = []
        self.outputs = []
    
    def forward(self, inputs, layer):
        weights = self.weights[layer]
        bias = self.biases[layer]
        if len(self.inputs) <= layer:
            self.inputs.append(inputs)
            self.outputs.append(np.dot(inputs, weights) + bias)
        else:
            self.inputs[layer] = inputs
            self.outputs[layer] = np.dot(inputs, weights) + bias
    
    def backward(self, dvalues, layer, lr):
        self.weights[layer] += lr * np.dot(self.inputs[layer].T,dvalues)
        self.biases[layer] += lr * np.sum(dvalues, axis=0, keepdims=True)
        self.dinputs = np.dot(dvalues, self.weights[layer].T)
    
    def predict(self, input_data):
        self.forward(input_data,0)
        self.tanh.forward(self.outputs[0],0)
        for layer in range(1, self.nLayers + 1):
            self.forward(self.tanh.outputs[layer - 1], layer)
            self.tanh.forward(self.outputs[layer], layer)
        return self.outputs[-1]
    
    def train(self, training_data, predicted_output, epochs, learning_rate):
        for epoch in range(epochs):
            out = self.predict(training_data)
            loss = np.mean(np.square(predicted_output - out))
            print(f"Epoch: {epoch + 1}, Loss: {loss}")
            self.tanh.backward(predicted_output - out, self.nLayers)
            self.backward(self.tanh.dinputs, self.nLayers, learning_rate)
            for layer in range(self.nLayers, 0):
                self.tanh.backward(self.dinputs, layer)
                self.backward(self.tanh.dinputs, layer, learning_rate)
    
class Tanh:
    def __init__(self):
        self.outputs = []
    
    def forward(self, inputs, layer):
        if len(self.outputs) <= layer:
            self.outputs.append(np.tanh(inputs))
        else:
            self.outputs[layer] = np.tanh(inputs)
    
    def backward(self, dvalues, layer):
        self.dinputs = dvalues * (1 - np.square(self.outputs[layer]))

if __name__ == "__main__":
    epochs = 50000
    learningRate = 0.08
    nLayers = 3
    nInputs = 5
    nOutputs = 1
    nNeurons = 1024
    iData = np.array([[0,0,0,0,0],[1,1,1,1,1],[1,0,1,0,1],[0,1,0,1,0],[1,1,0,0,1],[0,0,1,1,0],[0,1,1,0,0]])
    oData = np.array([[0],[1],[0],[1],[1],[0],[1]])
    NN = NeuralNetwork(nInputs, nNeurons, nOutputs, nLayers)
    NN.train(iData, oData, epochs, learningRate)
    print(NN.predict(np.array([[0,1,1,0,0]])))