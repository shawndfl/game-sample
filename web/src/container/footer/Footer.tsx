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
            <h1>Play the game!!</h1>
        </Container>

    </Box>
}
