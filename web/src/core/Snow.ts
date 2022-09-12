import {
    AdditiveBlending,
    BufferGeometry,
    Float32BufferAttribute,
    FogExp2,
    Points,
    PointsMaterial,
    Scene,
    Texture,
    TextureLoader
} from "three";

import snowflake1 from '../assets/img/snowflake1.png'
import snowflake2 from '../assets/img/snowflake2.png'
import snowflake3 from '../assets/img/snowflake3.png'
import snowflake4 from '../assets/img/snowflake4.png'
import snowflake5 from '../assets/img/snowflake5.png'

export class Snow {
    constructor(scene : Scene) {
        scene.fog = new FogExp2(0x000000, 0.0008);

        const geometry = new BufferGeometry();
        const vertices = [];

        const textureLoader = new TextureLoader();

        const sprite1 = textureLoader.load(snowflake1);
        const sprite2 = textureLoader.load(snowflake2);
        const sprite3 = textureLoader.load(snowflake3);
        const sprite4 = textureLoader.load(snowflake4);
        const sprite5 = textureLoader.load(snowflake5);

        for (let i = 0; i < 10000; i++) {

            const x = Math.random() * 2000 - 1000;
            const y = Math.random() * 2000 - 1000;
            const z = Math.random() * 2000 - 1000;

            vertices.push(x, y, z);

        }

        geometry.setAttribute('position', new Float32BufferAttribute(vertices, 3));

        const parameters = [
            [
                [
                    1.0, 0.2, 0.5
                ],
                sprite2,
                20
            ],
            [
                [
                    0.95, 0.1, 0.5
                ],
                sprite3,
                15
            ],
            [
                [
                    0.90, 0.05, 0.5
                ],
                sprite1,
                10
            ],
            [
                [
                    0.85, 0, 0.5
                ],
                sprite5,
                8
            ],
            [
                [
                    0.80, 0, 0.5
                ],
                sprite4,
                5
            ]
        ];

        for (let i = 0; i < parameters.length; i++) {

            const color = parameters[i][0] as number[];
            const sprite = parameters[i][1] as Texture;
            const size = parameters[i][2] as number;

            const materials = new PointsMaterial({
                size: size,
                map: sprite,
                blending: AdditiveBlending,
                depthTest: false,
                transparent: true
            });
            materials.color.setHSL(color[0], color[1], color[2]);

            const particles = new Points(geometry, materials);

            particles.rotation.x = Math.random() * 6;
            particles.rotation.y = Math.random() * 6;
            particles.rotation.z = Math.random() * 6;

            scene.add(particles);

        }

    }

}
