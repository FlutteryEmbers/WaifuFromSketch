#!/usr/bin/env python3

import numpy as np
from skimage import io
from skimage import transform
import matplotlib.pyplot as plt
import os
import torch
import torchvision
import torch.nn as nn
from torch.utils.data import Dataset, DataLoader
from torchvision.transforms import transforms
from torchvision.utils import make_grid
import math

EPOCH = 200           
BATCH_SIZE = 50
LR = 0.0001          



class CNN(nn.Module):
    def __init__(self):
        super(CNN, self).__init__()
        self.conv1 = nn.Sequential(  
            nn.Conv2d(
                in_channels=1,      # input height
                out_channels=16,    # n_filters
                kernel_size=5,      # filter size
                stride=1,           # filter movement/step
                padding=2,     
            ),      
            nn.ReLU(),    # activation
            nn.MaxPool2d(kernel_size=2),    
        )
        self.conv2 = nn.Sequential(  
            nn.Conv2d(16, 32, 7, 2, 2),  
            nn.ReLU(),  # activation
            nn.MaxPool2d(2),  
        )
        self.conv3 = nn.Sequential(  
            nn.Conv2d(32, 32, 5, 1, 2),  
            nn.ReLU(),  # activation
            nn.MaxPool2d(2),  
        )
        
        self.conv4 = nn.Sequential(  
            nn.Conv2d(32, 32, 3, 1, 2),  
            nn.ReLU(),  # activation

        )
        self.conv5 = nn.Sequential(  
            nn.Conv2d(32, 64, 3, 1, 2),  
            nn.ReLU(),  # activation
 
        )
        self.conv6 = nn.Sequential(  
            nn.Conv2d(64, 32, 3, 1, 2),  
            nn.ReLU(),  # activation
  
        )
        self.conv7 = nn.Sequential(  
            nn.Conv2d(32, 32, 3, 1, 2),  
            nn.ReLU(),  # activation
  
        )
        self.conv8 = nn.Sequential(  
            nn.Conv2d(32, 32, 3, 1, 2),  
            nn.ReLU(),  # activation
  
        )
        self.conv9 = nn.Sequential(  
            nn.Conv2d(32, 16, 3, 1, 2),  
            nn.ReLU(),  # activation
  
        )
        self.conv10 = nn.Sequential(  
            nn.Conv2d(16, 8, 3, 1, 2),  
            nn.ReLU(),  # activation

        )
        
        self.linear1 = nn.Linear(8192, 4096)   
        self.linear2 = nn.Linear(4096, 2048)   
        self.linear3 = nn.Linear(2048, 512)
        self.linear4 = nn.Linear(512, 128)
        self.linear5 = nn.Linear(128, 32)
        self.linear6 = nn.Linear(32, 22)

    def forward(self, x):
        x = self.conv1(x)
        x = self.conv2(x)
        x = self.conv3(x)
        x = self.conv4(x)
        x = self.conv5(x)
        x = self.conv6(x)
        x = self.conv7(x)
        x = self.conv8(x)
        x = self.conv9(x)
        x = self.conv10(x)
        x = x.view(x.size(0), -1)   
        x = self.linear1(x)
        x = self.linear2(x)
        x = self.linear3(x)
        x = self.linear4(x)
        x = self.linear5(x)
        output = self.linear6(x)
        return output


checkpoint = torch.load('24_cnn.pth')
cnn = CNN()
cnn.load_state_dict(checkpoint['net'])

optimizer = torch.optim.Adam(cnn.parameters(), lr=LR)   # optimize all cnn parameters
optimizer.load_state_dict(checkpoint['optimizer'])

loss_func = nn.MSELoss()   # the target label is not one-hotted

cnn.eval()
image = io.imread('./testing_painting/7003.png')
image_n = torch.from_numpy(image)
b_x = image_n.float().unsqueeze(0).unsqueeze(0)
output = cnn(b_x)
print(output.int())
