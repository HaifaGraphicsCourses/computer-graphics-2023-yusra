# Assignment2Report_part1
## Yusra Rayyan - 212896534  
### 1.
To draw the rectangle we find min x, min y, max x and max y and the draw teh recangle:
- (min_x, min_y).
- (min_x, max_y).
- (max_x, min_y).
- (max_x, max_y).
For each rectangle, we give it the color 
(255 – average z values, 36  – average z values,  – average z values) for the current polygon.
( 255,36,36) = red.

        glm::fvec2 c1, c2, c3, c4;
		c1 = glm::fvec2(min_x, min_y);
		c2 = glm::fvec2(min_x, max_y);
		c3 = glm::fvec2(max_x, min_y);
		c4 = glm::fvec2(max_x, max_y);
		float c_z = (Mesh.GetVertices(face.GetVertexIndex(0) - 1).z + Mesh.GetVertices(face.GetVertexIndex(1) - 1).z +
			Mesh.GetVertices(face.GetVertexIndex(1) - 1).z) / 3.0f;
		glm::vec3 color_rec = glm::vec3(255.0f / c_z, 36.0f / c_z, 36.0f / c_z);
		DrawLine(c1, c2, color_rec);
		DrawLine(c2, c3, color_rec);
		DrawLine(c3, c4, color_rec);
		DrawLine(c4, c1, color_rec);
	![2a_2.png](https://ams03pap003files.storage.live.com/y4mxJ3ghPLbWdhjBP0f_1CN1zm8YDZujTBaCSn1AaWzdO2om3hVldkWKo5Hjd6gQTw3LgyOQJQJtDzTEoi9jCemvWjaUR2uFcXDOuwFfrcGqMa8R7HWoYwglriEcIpCZaRSTnKm892R3ev2Z97yU2vA7RD3Auinvi3PvQk62XnWZg3E7O8ljgmUErjpnBZHihnh?width=1280&height=748&cropmode=none)
	after fixing
	![rec.png](https://ams03pap003files.storage.live.com/y4mouvWpL_OS2qDgsV4GtjqjyHS7qtBlMusslFu-0WNWPJ-5kQOof6zVYoiFivl8tW7cGBrITtxfY7y2hhj1ZkMp_lmQYmyam3h41iQ_EwYKk_TKgnStF5r8MXBHyC77CH0c7VGLcJxrF7YuFdX7qLTWyLtP6jmbp2Yop1LaYVTJurdVsvLAnmwYfH23UGCOK2P?width=1276&height=750&cropmode=none)
	

### 3. 
![23.png](https://ams03pap003files.storage.live.com/y4mrd2UrXBzzwA5VEEFWJfSVYEo2not90ctUUjOcFGJCp0kjy9Yi6ADyf8OQVU0cvAasYIRrWVWzmCkxhKH8ays0Y0pyy6cOr3mirf1F-u19YQ2IhUzed4W9HDYUXFRXN7PjjgA1Qc2Ml9W2IUPhuXs5Z3jmPT3wtNG72-LAh-HwYm11soxE7XPRa-CwwKlDDdY?width=1281&height=759&cropmode=none)
### 4. 
* color buffer:
![2a_4_1.png](https://ams03pap003files.storage.live.com/y4mFxLk-7e4fjUO0ldhSjWrUFfuVwh_20d7lseDqVHhcSot15KLH9E_kSYB5ou0xM_ZS4WoJmHy5z4gKhF1SDCGm7Yt-KKoAOikF2G7EPMUw3-dMNOsR77hsGCMr6wzRC4V_hee1YEOJa4qbcs6Z0Mhmnl6O0uwN65u3I9Zcm2d_ydSrc5coUn-ZVEfLHKc8E9J?width=1278&height=756&cropmode=none)
![2a_4_c.png](https://ams03pap003files.storage.live.com/y4m2-EuE5m60ZrUYGd8DJx7zs_foA_x6_fl9zlDlzYoENTbIPBE-lzFvygjnA0lzx3bXORB37sjBOz1N8ZwHY5cuRS-EP1RGE7TuZ3uTlUBldWZgANbZXS6gGl247Tlb7uQT6nC_v3lCE4igIl5BJlj777nGakXoE8PfjtDLFN5MBr7mDMC2vYkjAoJWB2bR4f5?width=1282&height=756&cropmode=none)
* z-buffer: 
![2a_4_z.png](https://ams03pap003files.storage.live.com/y4m1xxDgQoS54rs8sy41ato3HoKU_AOYwdGvQbepI_WWp1HvCAINIjFEtAaMoqz-aLvePcguzl_yfXvcQTscQ90ieoU4Waa9iSyLQOg8PNQ0BVuXjkw2EmGeVwLXXCoqro_3AzuYTRu_X_pk4b6JczNyAOSZVR-bVAOmcnifqFD5fsjX92p1R_q01Q1ofOUjz31?width=1284&height=764&cropmode=none)
after fixing:
![z.png](https://ams03pap003files.storage.live.com/y4m4Ku7Ggc9rlVnxJ25wfKv48uku_1q0ha2ZhaTZi6WzOZ_MxFsvH8aG47GG8LWi4APMwMaSo8zsDo-7HQWbYQI0AVckR-_4Jg6et8pa8cnM4eGbNtie_ia-RYBWpTlvxHYSGeR6WOMkMBiKR0YnENyvdQf37cFS9emZEsYaN07VQEpsN07NPxFDWZTt2uOKu0T?width=811&height=621&cropmode=none)
![z_d.png](https://ams03pap003files.storage.live.com/y4m8HUy5ieq5FoAwXQesM65iV7EfoQjfaxFUofvOiFmqF0qB4VrJw5GlbMfy1wWAqUy4HlKNY_wkJRjM5GIb9MN9GgMZjvye_mtNcl9PUkItajQa0D4bw1l0UClGqH7rnQ-A98FNXOEmQD7nX1KqDXHY6bwGlugxLG7O2bGtW0XbviPK7I7JbX0l0gkrGWtIdIx?width=1284&height=758&cropmode=none)
![c.png](https://ams03pap003files.storage.live.com/y4mUdX67D6v1gWvABuaevdLr4cSUy5aYDpoGs-CC0mdwNAulOKho9vR2XGZCSQ1kjPHAKT4acwviGQYnN7I8OfTyvNR_PiP1_kBofomkS2c9-5qx4ThxBPSvozI75Tt3JI3Ie7oxnG5CJrQbMQ-dMKyIRIeZXE-NOYgRsSh94Ye9iVI8my8Cy3WngE5exPETEkA?width=627&height=755&cropmode=none)