`define headerSize 1080
`define imageSize 512*512

module barbsim;
    integer file, i, file2;
    reg [7:0] imgdatabarb;  // Register to store individual bytes
    reg [7:0] image_data [0:`imageSize-1]; // Array to store all image data

    initial begin
        // Open the BMP file and the output header file
        file = $fopen("C:/Users/Sarvesh/Downloads/barbara_gray.bmp", "rb");
        file2 = $fopen("imgdatabarb.h", "w");

        // Check if the file is opened successfully
        if (file == 0) begin
            $display("Error: Failed to open the BMP file.");
            $finish;
        end else begin
            $display("File opened successfully.");
        end

        // Read the BMP file header and skip it
        for (i = 0; i < `headerSize; i = i + 1) begin
            $fscanf(file, "%c", imgdatabarb);
        end

        // Read the image data
        for (i = 0; i < `imageSize; i = i + 1) begin
            $fscanf(file, "%c", imgdatabarb);
            image_data[i] = imgdatabarb;
        end

        // Write the image data to the header file
        for (i = 0; i < `imageSize; i = i + 1) begin
            $fwrite(file2, "%0d,", image_data[i]);
        end

        // Close the files
        $fclose(file);
        $fclose(file2);

        $display("Image data successfully written to imgdatabarb.h");
    end
endmodule
