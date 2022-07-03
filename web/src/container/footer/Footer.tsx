import Box from "@mui/material/Box"
import {Container, Grid, Typography} from "@mui/material"

export default function Footer() {
    return <Box sx={
        {
            height: '50vh',
            backgroundColor: 'primary.dark'
        }
    }>
        <Container>
            <Grid container>
                <Grid item
                    sm={12} mt={2}>
                    <Typography variant="h4" component="h4" color="inherit">
                        About
                    </Typography>
                    <Typography variant="h6" component="h5" color="inherit">
                        I have been working with computer graphics for over 15 years now and have 
                        seen how graphics have progressed to an amazing level of realism, even within the web browser.
                        This simulation is using <a href="https://threejs.org/">ThreeJS</a> and is a very small sample of  
                        what ThreeJS can do.                         
                    </Typography>            

                    <Typography variant="h6" component="h5" color="inherit">                        
                    </Typography>                    
                    <Typography variant="h6" component="h5" color="inherit">
                        I hope to find some time to add more and maybe make it into a tutorial
                        We will see what happens...
                    </Typography>

                    
                </Grid>
            </Grid>
        </Container>

    </Box>
}
