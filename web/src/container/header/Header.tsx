import * as React from 'react';
import AppBar from '@mui/material/AppBar';
import Box from '@mui/material/Box';
import Toolbar from '@mui/material/Toolbar';
import Typography from '@mui/material/Typography';
import IconButton from '@mui/material/IconButton';
import GitHubIcon from '@mui/icons-material/GitHub';

export default function Header() {
  return (
    <Box sx={{ flexGrow: 1 }}>
      <AppBar position="static">
        <Toolbar className="tooBarBlack" >          
          <Typography variant="h4" component="h4" textAlign="center" sx={{ flexGrow: 1 }}>
            3D Simulation with ThreeJS
          </Typography>
          <IconButton component="a" target="_blank" href="https://github.com/shawndfl"><GitHubIcon/></IconButton>
        </Toolbar>
      </AppBar>
    </Box>
  );
}