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

EPOCH = 50           
BATCH_SIZE = 50
LR = 0.001          



class CNN(nn.Module):
    def __init__(self):
        super(CNN, self).__init__()
        self.conv1 = nn.Sequential(  
            nn.Conv2d(
                in_channels=1,      
                out_channels=16,    
                kernel_size=5,      
                stride=1,           
                padding=2,     
            ),      
            nn.ReLU(),   
            nn.MaxPool2d(kernel_size=2),    
        )
        self.conv2 = nn.Sequential(  
            nn.Conv2d(16, 32, 7, 2, 2),  
            nn.ReLU(), 
            nn.MaxPool2d(2),  
        )
        self.conv3 = nn.Sequential(  
            nn.Conv2d(32, 32, 5, 1, 2),  
            nn.ReLU(),   
            nn.MaxPool2d(2),  
        )
        
        self.conv4 = nn.Sequential(  
            nn.Conv2d(32, 32, 3, 1, 2),  
            nn.ReLU(),   

        )
        self.conv5 = nn.Sequential(  
            nn.Conv2d(32, 64, 3, 1, 2),  
            nn.ReLU(),   
 
        )
        self.conv6 = nn.Sequential(  
            nn.Conv2d(64, 32, 3, 1, 2),  
            nn.ReLU(),   
  
        )
        self.conv7 = nn.Sequential(  
            nn.Conv2d(32, 32, 3, 1, 2),  
            nn.ReLU(),   
  
        )
	
        self.conv8 = nn.Sequential(  
            nn.Conv2d(32, 32, 3, 1, 2),  
            nn.ReLU(),   
  
        )
        
        self.conv9 = nn.Sequential(  
            nn.Conv2d(32, 16, 3, 1, 2),  
            nn.ReLU(),   
  
        )
        self.conv10 = nn.Sequential(  
            nn.Conv2d(16, 8, 3, 1, 2),  
            nn.ReLU(),   

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

class MyDataset(Dataset):
    def __init__(self, root_dir, names_file, transform=None):
        self.root_dir = root_dir
        self.names_file = names_file
        self.transform = transform
        self.size = 0
        self.names_list = []

        if not os.path.isfile(self.names_file):
            print(self.names_file + 'does not exist!')
        file = open(self.names_file)
        for f in file:
            self.names_list.append(f)
            self.size += 1

    def __len__(self):
        return self.size

    def __getitem__(self, idx):
        image_path = self.root_dir + self.names_list[idx].split(',')[0]+".png"
        if not os.path.isfile(image_path):
            print(image_path + 'does not exist!')
            return None
        image = io.imread(image_path)   

        label = self.names_list[idx].split(',')[-22:]
        for i in range(21):
            label[i] = int(label[i])
        label[21] = int(label[21][0:-1])

        sample = {'image':torch.from_numpy(image), 'label': np.array(label)}
        if self.transform:
            sample = self.transform(sample)

        return sample
    


train_dataset = MyDataset(root_dir='./imagenew/train/',
                          names_file='./imagenew/train/pointdatatrain.csv',
                          transform=None)
test_dataset = MyDataset(root_dir='./imagenew/test/',
                          names_file='./imagenew/test/pointdatatest.csv',
                          transform=None)
trainset_dataloader = DataLoader(dataset=train_dataset,
                                 batch_size=100,
                                 shuffle=True,
                                 num_workers=4)
testset_dataloader = DataLoader(dataset=test_dataset,
                                 batch_size=2,
                                 shuffle=True,
                                 num_workers=4)
print("before")
#checkpoint = torch.load('4_cnn.pth')
cnn = CNN()
#cnn.load_state_dict(checkpoint['net'])
optimizer = torch.optim.Adam(cnn.parameters(), lr=LR)  
#optimizer.load_state_dict(checkpoint['optimizer'])
loss_func = nn.MSELoss()   

# training and testing
l_list=[]

f = open('./loss_data.txt', 'w')
for epoch in range(EPOCH):
    total_loss = 0.0
    print("epoch",epoch)
    l_o =[]
    for step,sample in enumerate(trainset_dataloader):  
        b_x = sample['image']
        b_x = b_x.float().unsqueeze(1)
        b_y = sample['label']
        output = cnn(b_x)              
        loss = loss_func(output, b_y.float())  
        print("loss",loss)
        l_o.append(loss.tolist())
        total_loss = total_loss + loss.tolist()
        optimizer.zero_grad()           
        loss.backward()                 
        optimizer.step()                
    total_loss = total_loss/step
    l_list.append(total_loss)
    f.write(str(l_o)+"\n")
    f.write(str(l_list)+"\n")
    if (epoch) % 1 == 0:
        f_name = "modn/"+str(epoch)+"_cnn.pth"
        state = {'net':cnn.state_dict(), 'optimizer':optimizer.state_dict(), 'epoch':epoch}
        torch.save(state,f_name)


f.close()
cnn.eval()
for step,sample in enumerate(testset_dataloader):  
    b_x = sample['image']
    b_x = b_x.float().unsqueeze(1)
    b_y = sample['label']
    output = cnn(b_x)
    print("__________________")
    print("real",b_y)     
    print("out",output.int())
    print("_________________")
    if step >11:
        break      



