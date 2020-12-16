open Core;;

let parse_line line =
  let open Angstrom in
  let parse parser = Result.ok_or_failwith (parse_string ~consume:All parser line) in
  let integer =
    take_while1 (function '0' .. '9' -> true | _ -> false) >>| int_of_string
  in
  parse integer

let _ =
  let lines = In_channel.read_lines "input" in
  let data = List.map ~f:parse_line lines in
  (* let prod = List.cartesian_product data data in *)
  (* let res = List.find_map_exn ~f:(fun (a, b) -> if a + b = 2020 then (Some (a*b)) else None) prod in *)
  let res = List.find_map_exn ~f:(fun x ->
    List.find_map ~f:(fun y ->
      List.find_map ~f:(fun z ->
        if x + y + z = 2020 then Some (x*y*z) else None  
      ) data
    ) data
  ) data
  in
  Out_channel.output_string stdout (string_of_int res)
